#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main() {
    int fd[2]; // 파이프 생성용 파일 디스크립터
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스: 파이프 읽기
        close(fd[1]); // 쓰기 끝 닫기
        char buffer[128];
        read(fd[0], buffer, sizeof(buffer)); // 부모로부터 데이터 읽기
        printf("Child received: %s\n", buffer);
        close(fd[0]); // 읽기 끝 닫기
        exit(0);
    } else {
        // 부모 프로세스: 파이프 쓰기
        close(fd[0]); // 읽기 끝 닫기
        char message[] = "Hello from parent!";
        write(fd[1], message, strlen(message) + 1); // 자식에게 데이터 쓰기
        close(fd[1]); // 쓰기 끝 닫기
        wait(NULL); // 자식 프로세스 종료 대기
    }

    return 0;
}

