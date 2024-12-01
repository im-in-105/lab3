#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) { // 자식 프로세스 3개 생성
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // 자식 프로세스
            printf("Child %d: PID %d, Parent PID %d\n", i, getpid(), getppid());
            exit(i); // 각 자식은 자신만의 종료 코드를 반환
        }
    }

    // 부모 프로세스
    for (int i = 0; i < 3; i++) {
        int status;
        pid_t child_pid = wait(&status); // 자식 프로세스 종료 대기
        if (WIFEXITED(status)) {
            printf("Parent: Child PID %d exited with status %d\n", child_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}

