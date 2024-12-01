#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 시그널 핸들러 함수
void handle_sigalrm(int sig) {
    printf("Timer expired! Signal %d (SIGALRM) received.\n", sig);
    exit(0);
}

int main() {
    // SIGALRM 시그널 핸들러 등록
    signal(SIGALRM, handle_sigalrm);

    printf("Setting a timer for 5 seconds...\n");
    alarm(5); // 5초 후 SIGALRM 발생

    while (1) {
        printf("Waiting for the timer...\n");
        sleep(1);
    }

    return 0;
}

