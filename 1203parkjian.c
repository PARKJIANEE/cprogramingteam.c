#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

// 매크로 정의
#define UP 0
#define DOWN 1
#define SUBMIT 2

// 전역 변수 선언
int totalQuestions = 22;

// 함수 선언
void init();
void titleDraw();
int menuDraw();
void gotoxy(int, int);
int keyControl();
void gameInfo();
void exitGame();
void gameStart();
void drawQuestion(int questionNumber, int totalQuestions, int x, int y);
int askQuestion(int questionNumber, int x, int y, int* correctAnswers);
void displayScore(int score, int x, int y);

char* questions[] = {
    "타이타닉의 구명 보트에는 몇 명이 탈수 있을까?",
    "개미네 집 주소는?",
    "금은 금인데 도둑고양이에게 가장 어울리는 금은?",
    "고기 먹을 때마다 따라오는 개는?",
    "별 중에 가장 슬픈 별은?",
    "진짜 새의 이름은 무엇일까요?",
    "붉은 길에 동전 하나가 떨어져 있다. 그 동전의 이름은?",
    "백가지 과일이 죽기 직전을 다른 말로?",
    "깨뜨리고 칭찬 받는 것은?",
    "청바지를 돋보이게 하는 걸음걸이는?",
    "못 사온다고 해놓고 사온 것은?",
    "운전하는 사람들이 가장 싫어하는 춤은?",
    "싸움을 잘하는 오리는?",
    "늘 청바지를 원하는 꽃은?",
    "양 중에서 가장 뜨거운 양은?",
    "좀비는 왜 멍청할까?",
    "[힘센 말과 고양이]를 네 글자로?",
    "돈인데, 결혼을 해야 생기는 돈은?",
    "사람들이 가장 좋아하는 영화는?",
    "아기돼지 삼 형제에서 한 마리가 더 늘어나면?",
    "한국은 원, 일본은 엔, 호주는?",
};

char* answers[] = {
    "9명",
    "허리도 가늘군 만지면 부러지리",
    "야금야금",
    "이쑤시개",
    "이별",
    "참새",
    "홍길동전",
    "백과사전",
    "신기록",
    "진주목걸이",
    "못",
    "우선멈춤",
    "을지문덕",
    "진달래",
    "태양",
    "머리가좀비어서",
    "슈퍼마켓",
    "사돈",
    "부귀영화",
    "모두 죽음",
    "호주머니",
};

int main() {
    init();
    titleDraw();

    int x = 1;
    int y = 7;

    gotoxy(x, y + 5);
    printf("\n         Press Enter to space...");
    while (keyControl() != SUBMIT);

    system("cls");

    int menuCode;
    do {
        menuCode = menuDraw();

        switch (menuCode) {
        case 1:
            gameStart();
            break;
        case 2:
            gameInfo();
            break;
        case 3:
            exitGame();
            break;
        }
    } while (menuCode != 3);

    return 0;
}

// 키 입력 제어 함수
int keyControl() {
    char temp = _getch();

    temp = toupper(temp);

    if (temp == ' ') {
        return SUBMIT;
    }
    else if (temp == 'Q' || temp == 'q') {
        exitGame();
    }

    return -1;
}

// 콘솔 초기화 함수
void init() {
    system("mode con cols=56 lines=20 | title 게임제목");
}

// 타이틀 화면 그리기 함수
void titleDraw() {
    int x = 1;
    int y = 7;
    printf("\n\n\n\n");
    gotoxy(x, y);
    printf("        #####       #     #       ##     #####      ##");
    gotoxy(x, y + 1);
    printf("       #     #      #     #                 #       ##");
    gotoxy(x, y + 2);
    printf("       #     #      #     #       ##     ###        ##");
    gotoxy(x, y + 3);
    printf("       #   # #      #     #       ##    #             ");
    gotoxy(x, y + 4);
    printf("        #####  #     #####        ##    #####       ##");
}

// 메뉴 표시 함수
int menuDraw() {
    int x = 28;
    int y = 7;

    // 콘솔 화면 지우기
    system("cls");

    // 가운데 정렬된 메뉴 옵션 표시
    gotoxy(x, y);
    printf("──────────────────");
    gotoxy(x, y + 1);
    printf(" 1. 게임 시작");
    gotoxy(x, y + 2);
    printf(" 2. 게임 정보");
    gotoxy(x, y + 3);
    printf(" 3. 종료  ");
    gotoxy(x, y + 4);
    printf("──────────────────");
    gotoxy(x, y + 5);
    printf("입력 창: ");

    int selectedOption = -1;

    // "입력 창"에서 사용자 입력 대기
    while (selectedOption < 0 || selectedOption > 3) {
        scanf("%d", &selectedOption);

        if (selectedOption < 1 || selectedOption > 3) {
            printf("유효하지 않은 입력입니다. 다시 입력하세요.\n");
            gotoxy(x + 11, y + 5);
            printf("            "); // 이전 입력 지우기
            gotoxy(x + 11, y + 5);
        }
    }

    // 선택한 메뉴 옵션 반환
    return selectedOption;
}

// 콘솔 커서 위치 이동 함수
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

// gameStart 함수
void gameStart() {
    int x = 1;
    int y = 1;

    // 화면 지우기
    system("cls");

    // 게임 로직 추가
    int correctAnswers = 0;
    int score = 0;
    int quitGame = 0; // Variable to track if the player wants to quit

    // 문제 순서 섞기
    int questionOrder[22];
    for (int i = 0; i < 22; ++i) {
        questionOrder[i] = i + 1; // 1부터 22까지의 숫자로 초기화
    }
    for (int i = 21; i > 0; --i) {
        int j = rand() % (i + 1);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[j];
        questionOrder[j] = temp;
    }

    for (int i = 0; i < 22; ++i) {
        // 문제 위에 메시지 표시
        gotoxy(x, y - 2);
        printf("'Q'를 눌러 종료하거나 계속 진행하세요.");

        // 'Q' 키 확인
        if (_kbhit()) {
            char key = _getch();
            key = toupper(key);
            if (key == 'Q') {
                quitGame = 1; // 게임 종료 플래그 설정
                break;
            }
        }

        if (askQuestion(questionOrder[i] + 1, x, y, &correctAnswers, &quitGame)) {
            // 정답일 경우에만 점수 계산
            score += 10;
        }

        // 문제마다 화면 지우기
        system("cls");

        if (!quitGame && correctAnswers == 0) {
            printf("'Q'를 눌러 종료하거나 계속 진행하세요.\n");
            break;
        }
    }

    if (!quitGame) {
        // Player did not quit during the game, display the score
        displayScore(score, x, y + 5);

        // 추가: 모든 문제를 풀고 나서 점수판 표시
        printf("\n\nPress Space to return to the main menu...");

        // Wait for Space key press
        while (keyControl() != SUBMIT);

        // Clear the screen
        system("cls");
    }
}


// 게임 종료 함수
void exitGame() {
    system("cls");
    printf("        #####    ##    ##    #    ##    ####    ##    ##\n");
    printf("        #              # #   #         #                \n");
    printf("        ###      ##    #  #  #    ##    ###     ##    ##\n");
    printf("        #        ##    #   # #    ##       #    ##    ##\n");
    printf("        #        ##    #    ##    ##   ####     ##    ##\n");
    // 정리 또는 작별 메시지 추가
    exit(0); // 프로그램 종료
}

// 문제 그리기 함수
void drawQuestion(int questionNumber, int x, int y) {
    gotoxy(x, y + 1);
    printf(" [문제 %d] %s\n", questionNumber, questions[questionNumber - 1 - 1]);
    gotoxy(x, y + 5);
    printf(" 답변: ");
}

// displayScore 함수 추가
void displayScore(int score, int x, int y) {
    gotoxy(x, y);
    printf("   ========================================");
    gotoxy(x, y + 1);
    printf("                     종료");
    gotoxy(x, y + 2);
    printf("   ========================================");
}

// askQuestion 함수 수정
int askQuestion(int questionNumber, int x, int y, int* correctAnswers, int* quitFlag) {
    char userAnswer[100];
    int isCorrect;

    do {
        // 문제 표시
        gotoxy(x, y + 1);
        printf(" [문제 %d] %s\n", questionNumber, questions[questionNumber - 1]);

        // 사용자 입력
        gotoxy(x, y + 5);
        printf(" 답변: ");
        gotoxy(x + 7, y + 5);
        scanf("%s", userAnswer);

        // 'Q' 키 확인
        if (_kbhit()) {
            char key = _getch();
            key = toupper(key);
            if (key == 'Q') {
                *quitFlag = 1; // 게임 종료 플래그 설정
                return 0;     // 질문이 답변되지 않았음을 나타냄
            }
        }

        // 사용자의 답과 정답 비교
        isCorrect = (strcmp(userAnswer, answers[questionNumber - 1]) == 0);

        // 결과 표시
        if (isCorrect) {
            gotoxy(x, y + 7);
            printf(" 정답입니다! (+10점)\n");
            (*correctAnswers)++;
        }
        else {
            gotoxy(x, y + 7);
            printf(" 틀렸습니다. 정답은 %s입니다.\n", answers[questionNumber - 1]);
            Sleep(1000);
            break;
        }

        // 정답 또는 오답 메시지 표시 후 짧은 지연
        Sleep(1000);

        // 각 문제마다 화면 지우기
        system("cls");

        // 추가: 마지막 문제인 경우 결과 표시
        if (questionNumber == 22) {
            displayScore(*correctAnswers * 10, x, y + 5);
            printf("\n\nPress Space to return to the main menu...");

            // Wait for Space key press
            while (keyControl() != SUBMIT);

            // Clear the screen
            system("cls");
        }

    } while (!isCorrect);

    return isCorrect; // 정답 여부 반환
}

void gameInfo() {
    int x = 28;
    int y = 7;

    // 콘솔 화면 지우기
    system("cls");

    printf("\n\n\n\n");
    printf("여러가지의 난센스 퀴즈를 풀 수 있는 간단한 콘솔 게임 입니다!\n\n");
    printf("게임 중간에 종료 하고 싶다면 'Q'를 눌러주시면 됩니다.\n\n");
    printf("재밌는 22문제의 난센스 퀴즈를 풀어보세요\n\n\n");
    // You may want to add additional information or instructions here.
    printf("Press Space to return to the main menu...");

    // Wait for Space key press
    while (keyControl() != SUBMIT);

    // Clear the screen
    system("cls");

    // Display the main menu again
    do {
        // 콘솔 화면 지우기
        system("cls");

        // 가운데 정렬된 메뉴 옵션 표시
        gotoxy(x, y);
        printf("──────────────────");
        gotoxy(x, y + 1);
        printf(" 1. 게임 시작");
        gotoxy(x, y + 2);
        printf(" 2. 게임 정보");
        gotoxy(x, y + 3);
        printf(" 3. 종료  ");
        gotoxy(x, y + 4);
        printf("──────────────────");
        gotoxy(x, y + 5);
        printf("입력 창: ");

        int selectedOption = -1;

        // "입력 창"에서 사용자 입력 대기
        while (selectedOption < 0 || selectedOption > 3) {
            scanf("%d", &selectedOption);

            if (selectedOption < 1 || selectedOption > 3) {
                printf("유효하지 않은 입력입니다. 다시 입력하세요.\n");
                gotoxy(x + 11, y + 5);
                printf("            "); // 이전 입력 지우기
                gotoxy(x + 11, y + 5);
            }
        }

        // 메뉴에 따른 동작 수행
        switch (selectedOption) {
        case 1:
            // 게임 시작
            gameStart();
            break;
        case 2:
            // 게임 정보 챕터
            // 추가적인 정보를 표시하거나 작업을 수행할 수 있음
            break;
        case 3:
            // 종료
            exitGame();
            break;
        default:
            printf("유효하지 않은 입력입니다. 다시 선택하세요.\n");
        }

    } while (1);
}
