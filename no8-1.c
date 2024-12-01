#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 시그널 핸들러 함수
void handle_sigint(int sig) {
    printf("Caught signal %d (SIGINT). Exiting gracefully.\n", sig);
    exit(0);
}

int main() {
    // SIGINT 시그널 핸들러 등록
    signal(SIGINT, handle_sigint);

    printf("Running... Press Ctrl-C to send SIGINT.\n");
    while (1) {
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}

