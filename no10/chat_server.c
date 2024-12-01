#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 100

// 메시지 구조체
struct msg_buffer {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 메시지 큐의 고유 키 생성
    if ((key = ftok("chat_server.c", 65)) == -1) {
        perror("ftok failed");
        exit(1);
    }

    // 메시지 큐 생성
    if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Server started. Waiting for messages...\n");

    // 메시지를 계속 받는 무한 루프
    while (1) {
        // 메시지 큐에서 메시지를 수신
        if (msgrcv(msgid, &message, sizeof(message), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        // 메시지 출력
        printf("Client: %s", message.msg_text);

        // 종료 메시지 처리
        if (strcmp(message.msg_text, "exit\n") == 0) {
            printf("Server: Exiting...\n");
            break;
        }
    }

    // 메시지 큐 제거
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

