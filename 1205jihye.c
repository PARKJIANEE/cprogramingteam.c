#include <stdio.h>

int main() {
    char answers[] = { 'O', 'X', 'O', 'O', 'X', 'O', 'X', 'X', 'O', 'X' };
    char user_answers[10];
    int score = 0;

    printf("OX 퀴즈를 시작합니다.\n");
    printf("문제에 대한 답을 O 또는 X로 입력해주세요.\n");

    // 문제 출력과 사용자 답변 입력
    for (int i = 0; i < 10; i++) {
        printf("\n문제 %d:\n", i + 1);

        // 각 문제에 대한 printf로 제시
        switch (i) {
        case 0:
            printf("세계에서 가장 큰 대륙은 아시아이다. (O/X)\n");
            break;
        case 1:
            printf("태양계에서 지구는 3번째로 가까운 행성이다. (O/X)\n");
            break;
        case 2:
            printf("물은 화학식으로 H2O이다. (O/X)\n");
            break;
        case 3:
            printf("프랑스의 수도는 파리이다. (O/X)\n");
            break;
        case 4:
            printf("5+7은 10이다. (O/X)\n");
            break;
        case 5:
            printf("인간의 심장은 평균적으로 70 ~ 80회 심박수를 가진다. (O/X)\n");
            break;
        case 6:
            printf("네덜란드의 수도는 암스테르담이다. (O/X)\n");
            break;
        case 7:
            printf("포카혼타스는 애니메이션 영화 주인공이다. (O/X)\n");
            break;
        case 8:
            printf("독수리는 하루에 여러 번 먹이를 먹는다. (O/X)\n");
            break;
        case 9:
            printf("바다의 색은 항상 푸르다. (O/X)\n");
            break;
        default:
            break;
        }

        printf("O 또는 X 입력: ");
        scanf(" %c", &user_answers[i]);

        // 정답 확인
        if (user_answers[i] == answers[i]) {
            printf("정답입니다!\n");
            score++;
        }
        else {
            printf("오답입니다.\n");
        }

        // 버퍼 비우기
        while (getchar() != '\n');
    }

    printf("\n퀴즈 종료! 총 점수: %d / 10\n", score);

    return 0;
}
