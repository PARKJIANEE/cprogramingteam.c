#include <stdio.h>
#include <stdlib.h>

void game1();
void game2();
void game3();
void game4();

int main() {
    int choice;

    do {
        printf("게임을 선택하세요:\n");
        printf("=======================\n");
        printf("1. 상식 퀴즈 게임\n");
        printf("2. 공룡 게임\n");
        printf("3. 넌센스 퀴즈 게임\n");
        printf("4. 테트리스 게임\n");
        printf("5. 종료\n");
        printf("=======================\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            game1();
            break;
        case 2:
            game2();
            break;
        case 3:
            game3();
            break;
        case 4:
            game4();
            break;
        case 5:
            printf("게임을 종료합니다.\n");
            break;
        default:
            printf("유효하지 않은 입력입니다. 다시 선택하세요.\n");
        }
    } while (choice != 5);

    return 0;
}

void game1() {
    char answers[] = { 'O', 'X', 'O', 'O', 'X', 'O', 'X', 'X', 'O', 'X' };
    char user_answers[10];
    int score = 0;

    printf("OX 퀴즈를 시작합니다.\n");
    printf("문제에 대한 답을 O 또는 X로 입력해주세요.\n");

    for (int i = 0; i < 10; i++) {
        printf("\n문제 %d:\n", i + 1);

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

        if (user_answers[i] == answers[i]) {
            printf("정답입니다!\n");
            score++;
        }
        else {
            printf("오답입니다.\n");
        }

        while (getchar() != '\n');
    }

    printf("\n퀴즈 종료! 총 점수: %d / 10\n", score);
}

void game2() {
    printf("게임 2 실행!\n");
}

void game3() {
    printf("게임 3 실행!\n");
}

void game4() {
    printf("게임 4 실행!\n");

}