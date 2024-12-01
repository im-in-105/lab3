#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2]; // 파이프 파일 디스크립터
    pid_t pid;
    char buffer[100];

    // 파이프 생성
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork(); // 자식 프로세스 생성

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) { // 자식 프로세스
        close(fd[0]); // 읽기 끝 닫기
        char message[] = "Hello from child!";
        write(fd[1], message, sizeof(message));
        close(fd[1]); // 쓰기 끝 닫기
    } else { // 부모 프로세스
        close(fd[1]); // 쓰기 끝 닫기
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd[0]); // 읽기 끝 닫기
    }

    return 0;
}

