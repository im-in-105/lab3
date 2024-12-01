#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    key_t key = 1234; // 공유 메모리 키
    int shmid;
    char *shared_memory;

    // 공유 메모리 생성
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) { // 자식 프로세스
        shared_memory = (char *)shmat(shmid, NULL, 0); // 공유 메모리 첨부
        strcpy(shared_memory, "Hello from child!"); // 메시지 작성
        shmdt(shared_memory); // 공유 메모리 분리
    } else { // 부모 프로세스
        wait(NULL); // 자식 프로세스 종료 대기
        shared_memory = (char *)shmat(shmid, NULL, 0); // 공유 메모리 첨부
        printf("Parent received: %s\n", shared_memory);
        shmdt(shared_memory); // 공유 메모리 분리
        shmctl(shmid, IPC_RMID, NULL); // 공유 메모리 제거
    }

    return 0;
}

