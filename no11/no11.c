#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>  // 추가: wait 함수 사용을 위해 필요

#define SHM_SIZE 1024  // 공유 메모리 크기
#define SEM_KEY 1234   // 세마포어 키

// 세마포어 연산을 위한 함수
void sem_wait(int sem_id) {
    struct sembuf sb = {0, -1, 0};
    semop(sem_id, &sb, 1);
}

void sem_signal(int sem_id) {
    struct sembuf sb = {0, 1, 0};
    semop(sem_id, &sb, 1);
}

int main() {
    // 세마포어 생성
    int sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }
    semctl(sem_id, 0, SETVAL, 1);  // 세마포어 초기화
    printf("Semaphore created.\n");

    // 공유 메모리 생성
    key_t key = ftok("file_copy", 65);
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }
    printf("Shared memory created.\n");

    // 공유 메모리 연결
    char *shm_ptr = (char*) shmat(shm_id, NULL, 0);
    if (shm_ptr == (char*) -1) {
        perror("shmat failed");
        exit(1);
    }
    printf("Shared memory attached.\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // 자식 프로세스 (파일을 공유 메모리로 복사)
        FILE *src_file = fopen("source.txt", "r");
        if (src_file == NULL) {
            perror("source file open failed");
            exit(1);
        }
        printf("Source file opened by child process.\n");

        // 세마포어를 통해 부모 프로세스가 읽고 있는 데이터를 쓸 수 없도록 동기화
        sem_wait(sem_id);

        // 파일 내용을 공유 메모리에 복사
        size_t bytes_read;
        while ((bytes_read = fread(shm_ptr, 1, SHM_SIZE, src_file)) > 0) {
            shm_ptr[bytes_read] = '\0';  // NULL로 끝내기
            sem_signal(sem_id);  // 데이터 쓰기 완료 후 세마포어 신호
            sem_wait(sem_id);    // 데이터 읽기 완료까지 기다리기
        }

        fclose(src_file);
        printf("Child process finished.\n");
        exit(0);

    } else {
        // 부모 프로세스 (공유 메모리에서 데이터를 읽어 다른 파일에 저장)
        FILE *dest_file = fopen("destination.txt", "w");
        if (dest_file == NULL) {
            perror("destination file open failed");
            exit(1);
        }
        printf("Destination file opened by parent process.\n");

        // 세마포어를 통해 자식 프로세스가 데이터를 쓸 수 없도록 동기화
        sem_wait(sem_id);

        while (1) {
            // 공유 메모리에서 읽은 데이터를 destination.txt에 쓴다.
            fprintf(dest_file, "%s", shm_ptr);
            fflush(dest_file);

            // 자식 프로세스가 데이터를 계속 쓸 수 있도록 세마포어 신호
            sem_signal(sem_id);

            // 데이터를 모두 읽으면 종료
            if (feof(dest_file)) {
                break;
            }

            sem_wait(sem_id);  // 자식 프로세스가 다시 데이터를 쓰는 동안 기다리기
        }

        fclose(dest_file);
        printf("Parent process finished. Waiting for child.\n");

        wait(NULL);  // 자식 프로세스 종료 대기
    }

    // 공유 메모리와 세마포어 해제
    shmdt(shm_ptr);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    printf("Shared memory and semaphore cleaned up.\n");

    return 0;
}

