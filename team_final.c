// 랜덤 도어락 비밀번호 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// 함수 선언
int generate_random_password(int length);

int main() {
    srand((unsigned int)time(NULL));

    char original_password[1001];
    int user_input = -1; // 사용자 입력 초기화
    int attempts = 0;
    const int max_attempts = 3;

    // 초기 비밀번호 입력 및 확인
    do {
        printf("초기 비밀번호를 입력하세요: ");
        if (fgets(original_password, sizeof(original_password), stdin) == NULL) {
            printf("입력 오류가 발생했습니다.\n");
            return 1;
        }

        size_t len = strlen(original_password);
        if (len > 0 && original_password[len - 1] == '\n') {
            original_password[len - 1] = '\0';
        }

        int original_password_value = atoi(original_password);
        if (strlen(original_password) >= 4 && strlen(original_password) <= 8 && original_password_value >= 0) {
            printf("\n비밀번호를 확인하였습니다. 메뉴를 띄웁니다.\n");
            break;
        }
        else {
            attempts++;
            printf("\n비밀번호가 4 ~ 8자리이어야 하며, 다시 입력하세요. (남은 시도 횟수: %d)\n", max_attempts - attempts);
            if (attempts >= max_attempts) {
                printf("3번의 시도를 초과하여 프로그램을 종료합니다.\n");
                return 0;
            }
        }
    } while (1);

    // 메인 메뉴
    while (true) {
        printf("==============================\n");
        printf("1. 비밀번호 입력하기\n"); // case 1 
        printf("2. 새로운 랜덤 비밀번호 받기\n"); // case 2
        printf("3. 종료\n"); // case 3
        printf("==============================\n");
        printf("번호를 입력하세요: ");

        int menu_choice;
        scanf("%d", &menu_choice);

        switch (menu_choice) {
        case 1: { // 1. 초기 비밀번호 입력하기
            int entered_password;
            int confirm_password;
            int wrong_attempts = 0; // 잘못된 시도 횟수 초기화
            do {
                printf("새로운 비밀번호를 입력하세요: ");
                scanf("%d", &entered_password);

                printf("새로운 비밀번호를 다시 입력해보세요: ");
                scanf("%d", &confirm_password);

                if (entered_password != confirm_password) {
                    printf("입력한 두 비밀번호가 일치하지 않습니다.\n\n");
                    wrong_attempts++; // 틀린 시도 횟수 증가

                    if (wrong_attempts >= max_attempts) {
                        printf("세 번 이상의 잘못된 시도로 인해 프로그램을 종료합니다.\n");
                        return 0; // 비밀번호 불일치로 인한 종료
                    }

                    continue; // 두 비밀번호가 일치하지 않으면 다시 입력 요청
                }

                if (entered_password == atoi(original_password)) {
                    printf("이전의 비밀번호와 동일합니다. 다른 비밀번호를 선택하세요.\n");
                    break;
                }

                user_input = entered_password;
                printf("\n비밀번호가 설정되었습니다.\n");
                return 0; // 비밀번호 설정 후 프로그램 종료
            } while (1);

            break;
        }


        case 2: { // 2. 새로운 랜덤 비밀번호 받기
            printf("==========================\n");
            printf("1. 4자리 랜덤 비밀번호\n");
            printf("2. 8자리 랜덤 비밀번호\n");
            printf("3. 4~8자리 랜덤 비밀번호\n");
            printf("==========================\n");
            printf("비밀번호 길이를 선택하세요 (1, 2, 3): ");

            int password_length;
            scanf("%d", &password_length);

            if (password_length == 1 || password_length == 2 || password_length == 3) {
                int new_password;
                if (password_length == 1) { // 4자리 랜덤 비밀번호
                    new_password = generate_random_password(4);
                    printf("새로운 비밀번호 입니다: %04d\n", new_password);
                }
                else if (password_length == 2) { // 8자리 랜덤 비밀번호
                    new_password = generate_random_password(8);
                    printf("새로운 비밀번호 입니다: %08d\n", new_password);
                }
                else if (password_length == 3) { // 4~8자리 랜덤 비밀번호
                    new_password = generate_random_password(rand() % 5 + 4);
                    printf("새로운 비밀번호 입니다: %0*d\n", rand() % 5 + 4, new_password);
                }

                int entered_password;
                do {
                    printf("새로운 비밀번호를 입력해보세요: ");
                    scanf("%d", &entered_password);

                    if (new_password == entered_password) {
                        printf("비밀번호가 설정되었습니다.\n");
                        return 0;
                    }
                    else {
                        attempts++;
                        if (attempts >= max_attempts) {
                            printf("\n세 번 이상의 잘못된 시도로 인해 프로그램을 종료합니다.\n");
                            return 0; // 세 번 이상의 잘못된 시도로 인한 종료
                        }
                        printf("\n정확하지 않은 비밀번호입니다. 다시 입력하세요. (남은 시도 횟수: %d)\n", max_attempts - attempts);
                    }
                } while (1); // 올바른 비밀번호를 입력할 때까지 반복
            }
            else {
                printf("잘못된 선택입니다.\n");
            }

            break;
        }


        case 3: { // 3. 종료
            printf("기존 비밀번호로 유지합니다.\n");
            return 0;
        }

        default:
            printf("잘못된 선택입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}

int generate_random_password(int length) {
    int max_value = 1;
    for (int i = 0; i < length; ++i) {
        max_value *= 10;
    }

    return rand() % max_value;
}
