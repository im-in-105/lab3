#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// SIGINT (Ctrl-C) 핸들러
void handle_sigint(int sig) {
    printf("\nCaught signal %d (SIGINT). Exiting gracefully...\n", sig);
    exit(0); // 프로그램 종료
}

// SIGQUIT (Ctrl-\) 핸들러
void handle_sigquit(int sig) {
    printf("\nCaught signal %d (SIGQUIT). Ignoring and resuming...\n", sig);
    // 원하는 동작을 정의하거나, 단순히 무시하고 계속 실행
}

// SIGTSTP (Ctrl-Z) 핸들러
void handle_sigtstp(int sig) {
    printf("\nCaught signal %d (SIGTSTP). Stopping is disabled. Resuming...\n", sig);
    // SIGTSTP 기본 동작 방지 (무시)
}

int main() {
    // SIGINT, SIGQUIT, SIGTSTP에 대한 핸들러 등록
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
    signal(SIGTSTP, handle_sigtstp);

    printf("Program running. Press Ctrl-C to exit, Ctrl-\\ to test SIGQUIT, or Ctrl-Z to test SIGTSTP handling.\n");

    // 무한 루프
    while (1) {
        printf("Running...\n");
        sleep(2); // 2초 대기
    }

    return 0;
}

