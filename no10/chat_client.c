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

    // 메시지 큐에 접근
    if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    // 무한 루프에서 사용자로부터 입력받은 메시지를 계속 전송
    while (1) {
        // 사용자로부터 입력받은 메시지 전송
        printf("Enter message: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);

        message.msg_type = 1; // 메시지 유형 지정 (여기서는 1)

        // 메시지 큐에 메시지 전송
        if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

        // 종료 메시지 처리
        if (strcmp(message.msg_text, "exit\n") == 0) {
            break;
        }
    }

    return 0;
}

