#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>  // strcat 함수를 사용하기 위한 헤더 파일 추가

// system 함수처럼 쉘 명령어를 실행하는 함수
int my_system(const char *command) {
    pid_t pid = fork();  // 자식 프로세스를 생성

    if (pid == -1) {
        perror("fork failed");
        return -1;  // fork 실패
    } 
    else if (pid == 0) {
        // 자식 프로세스에서 실행
        char *args[] = {"/bin/sh", "-c", (char *)command, NULL};
        
        if (execvp(args[0], args) == -1) {  // 쉘 명령어 실행
            perror("execvp failed");
            exit(1);  // execvp 실패 시 종료
        }
    } 
    else {
        // 부모 프로세스에서 대기
        waitpid(pid, NULL, 0);  // 자식 프로세스가 종료될 때까지 대기
    }
    
    return 0;  // 명령어 실행 완료
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // 인수로 받은 명령어 실행
    char command[1024] = {0};
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);  // 명령어 이어붙이기
        if (i != argc - 1) {
            strcat(command, " ");  // 공백 추가
        }
    }

    // my_system을 이용해 명령어 실행
    printf("Executing command: %s\n", command);
    my_system(command);

    return 0;
}

