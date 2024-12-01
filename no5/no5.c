#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    char target[] = "난 내가 좋아 정말 난 내가 좋아 이 세상에서 가장 소중한 선물.";
    char input[100];
    int mistakes = 0;
    int correct_chars = 0;
    clock_t start_time, end_time;

    // 타자 연습 문장 출력
    printf("타자 연습 문장: %s\n", target);
    printf("위 문장을 타이핑하세요: ");

    // 타이핑 시작 시간 측정
    start_time = clock();

    // 사용자 입력 받기
    fgets(input, sizeof(input), stdin);

    // 타이핑 종료 시간 측정
    end_time = clock();

    // 입력된 문장에서 줄바꿈 제거
    input[strcspn(input, "\n")] = '\0';

    // 입력이 정확한지 확인
    for (int i = 0; i < strlen(target); i++) {
        if (input[i] != target[i]) {
            mistakes++;  // 잘못 타이핑한 문자 카운트
        } else {
            correct_chars++;  // 정확하게 타이핑한 문자 카운트
        }
    }

    // 타이핑 시간 계산 (초 단위)
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // 분당 타자수 계산
    double typing_speed = (correct_chars / time_taken) * 60;

    // 결과 출력
    printf("\n타이핑 결과:\n");
    printf("잘못 타이핑한 횟수: %d\n", mistakes);
    printf("평균 분당 타자수: %.2f\n", typing_speed);

    return 0;
}

