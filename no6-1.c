#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스 실행
        printf("This is the child process. PID: %d\n", getpid());
        execlp("/bin/ls", "ls", "-l", NULL); // exec 함수로 ls 명령 실행
        perror("execlp failed"); // exec 함수 실패 시 오류 출력
        exit(1);
    } else {
        // 부모 프로세스 실행
        printf("This is the parent process. PID: %d, Waiting for child...\n", getpid());
        int status;
        wait(&status); // 자식 프로세스가 끝날 때까지 대기
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }
    }
    return 0;
}

