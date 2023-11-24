// 랜덤 도어락 비밀번호 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// 함수 선언
int generate_random_password(int length);

int main() {
    srand((unsigned int)time(NULL));

    int original_password;
    int user_input = -1; // 사용자 입력 초기화
    int attempts = 0;
    const int max_attempts = 3;

    while (true) {
        printf("==============================\n");
        printf("1. 초기 비밀번호 입력하기\n"); // case 1 
        printf("2. 새로운 랜덤 비밀번호 받기\n"); // case 2
        printf("3. 종료\n"); // case 3
        printf("==============================\n");
        printf("번호를 입력하세요: ");

        int menu_choice;
        scanf("%d", &menu_choice);

        switch (menu_choice) {
        case 1: { // 1. 초기 비밀번호 입력하기
            // 사용자에게 초기 비밀번호 길이 입력 받기
            int password_length;
            printf("초기 비밀번호의 길이를 선택하세요 (4 또는 8): ");
            scanf("%d", &password_length);

            if (password_length == 4 || password_length == 8) {
                do {
                    printf("초기 비밀번호를 입력하세요: ");
                    scanf("%d", &original_password);

                    // 사용자에게 비밀번호 입력 받기
                    int entered_password;
                    do {
                        printf("\n비밀번호를 다시 입력하세요: ");
                        scanf("%d", &entered_password);

                        if (entered_password != original_password) {
                            attempts++;
                            printf("비밀번호가 일치하지 않습니다. 다시 입력하세요. (남은 시도 횟수: %d)\n", max_attempts - attempts);
                            if (attempts >= max_attempts) {
                                printf("3번의 시도를 초과하여 프로그램을 종료합니다.\n");
                                return 0;
                            }
                        }
                        else {
                            user_input = entered_password;
                            printf("\n비밀번호를 설정하셨습니다.");
                            return 0;
                        }
                    } while (1);

                } while (1);

            }
            else {
                printf("잘못된 길이를 선택하셨습니다. 초기화면으로 돌아갑니다.\n");
            }
            break;
        }

        case 2: { // 2. 새로운 랜덤 비밀번호 받기
            printf("======================\n");
            printf("4. 4자리 랜덤 비밀번호\n");
            printf("5. 8자리 랜덤 비밀번호\n");
            printf("======================\n");
            printf("비밀번호 길이를 선택하세요 (4 또는 8): ");

            int password_length;
            scanf("%d", &password_length);

            if (password_length == 4 || password_length == 8) {
                int new_password = generate_random_password(password_length);
                printf("새로운 비밀번호 입니다: %0*d\n", password_length, new_password);

                // 비밀번호 비교
                if (user_input != -1) {
                    int debug_input;
                    printf("\n새로운 패스워드를 입력하세요: ");
                    scanf("%d", &debug_input);
                    if (debug_input == user_input) {
                        printf("이전의 패스워드를 입력하였습니다.\n");
                    }
                    else if (debug_input == original_password) {
                        printf("새로운 패스워드를 입력하였습니다.\n");
                    }
                    else {
                        printf("잘못된 비밀번호입니다.\n");
                    }
                }
            }
            else {
                printf("잘못된 길이를 선택하셨습니다.\n");
            }

            break;
        }

        case 3: { // 3. 종료
            printf("프로그램을 종료합니다.\n");
            return 0;
        }

        default:
            printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}

// 랜덤 비밀번호 생성 함수
int generate_random_password(int length) {
    int max_value = 1;
    for (int i = 0; i < length; ++i) {
        max_value *= 10;
    }

    return rand() % max_value;
}

