# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Diary {
    char date[12];
    char mood[20];
    char content[200];
    int rating;  // 1부터 5까지의 별점
};

void addDiary(struct Diary diary) {
    FILE* file = fopen("diary.txt", "a");
    if (file == NULL) {
        printf("일기 파일을 열 수 없습니다.\n");
        exit(1);
    }

    fprintf(file, "%s %s %s %d\n", diary.date, diary.mood, diary.content, diary.rating);

    fclose(file);
}

void viewDiary(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("일기 파일을 열 수 없습니다.\n");
        exit(1);
    }

    struct Diary diary;
    int found = 0;

    while (fscanf(file, "%s %s %[^\n] %d", diary.date, diary.mood, diary.content, &diary.rating) != EOF) {
        if (strcmp(diary.date, date) == 0) {
            char* colorCode = "";
            if (strcmp(diary.mood, "기쁨") == 0) {
                colorCode = "\033[1;33m"; // 노란색
            }
            else if (strcmp(diary.mood, "슬픔") == 0) {
                colorCode = "\033[1;34m"; // 파란색
            }
            else if (strcmp(diary.mood, "까칠") == 0) {
                colorCode = "\033[1;32m"; // 초록색
            }
            else if (strcmp(diary.mood, "화남") == 0) {
                colorCode = "\033[1;31m"; // 빨간색
            }
            else if (strcmp(diary.mood, "소심") == 0) {
                colorCode = "\033[1;35m"; // 보라색
            }

            printf("%s", colorCode);
            printf("=== %s의 일기 ===\n", date);
            printf("기분: %s\n", diary.mood);
            printf("내용: %s\n", diary.content);

            // 총점에 따라 별을 출력
            printf("별점: ");
            for (int i = 0; i < diary.rating; ++i) {
                printf("★");
            }
            printf("\n");

            printf("==================\n");

            // 원래의 색상으로 복구
            printf("\033[0m");
            found = 1;
        }
    }

    if (!found) {
        printf("%s의 일기가 없습니다.\n", date);
    }

    fclose(file);
}

int calculateTotalRating(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("일기 파일을 열 수 없습니다.\n");
        exit(1);
    }

    struct Diary diary;
    int totalRating = 0;

    while (fscanf(file, "%s %*s %*[^ ] %d", diary.date, &diary.rating) != EOF) {
        if (strcmp(diary.date, date) == 0) {
            totalRating += diary.rating;
        }
    }

    fclose(file);

    return totalRating;
}

void clearDiaryFile() {
    FILE* file = fopen("diary.txt", "w");
    if (file == NULL) {
        printf("일기 파일을 열 수 없습니다.\n");
        exit(1);
    }
    fclose(file);
}

void clearAllDiaries() {
    printf("모든 일기를 삭제하시겠습니까? (1: 예, 2: 아니오): ");
    int clearChoice;
    scanf("%d", &clearChoice);
    if (clearChoice == 1) {
        clearDiaryFile();
        printf("모든 일기가 삭제되었습니다.\n");
    }
    else {
        printf("일기 삭제를 취소했습니다.\n");
    }
}

void deleteDiaryByDate(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("일기 파일을 열 수 없습니다.\n");
        exit(1);
    }

    FILE* tempFile = fopen("temp_diary.txt", "w");
    if (tempFile == NULL) {
        printf("일기 임시 파일을 열 수 없습니다.\n");
        exit(1);
    }

    struct Diary diary;
    int deleted = 0;

    while (fscanf(file, "%s %*s %*[^ ] %*d", diary.date) != EOF) {
        if (strcmp(diary.date, date) == 0) {
            deleted = 1;
        }
        else {
            fprintf(tempFile, "%s\n", diary.date);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("diary.txt");
    rename("temp_diary.txt", "diary.txt");

    if (deleted) {
        printf("%s의 일기가 삭제되었습니다.\n", date);
    }
    else {
        printf("%s의 일기가 없습니다.\n", date);
    }
}

void printMenu() {
    printf("=== 메뉴 ===\n");
    printf("1. 일기 쓰기\n");
    printf("2. 특정 날짜의 일기 보기\n");
    printf("3. 날짜의 총점 확인\n");
    printf("4. 모든 일기 초기화\n");
    printf("5. 특정 날짜의 일기 삭제\n");
    printf("6. 프로그램 종료\n");
    printf("============\n");
    printf("메뉴를 선택하세요: ");
}

int main() {
    int choice;
    struct Diary diary;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("오늘의 날짜를 입력하세요 (YYYY.MM.DD): ");
            scanf("%s", diary.date);

            printf("기분을 선택하세요 (기쁨, 슬픔, 까칠, 화남, 소심 등): ");
            scanf("%s", diary.mood);

            printf("두 세 문장으로 오늘의 일기를 작성하세요: ");
            getchar();  // 버퍼 비우기
            fgets(diary.content, sizeof(diary.content), stdin);

            printf("별점을 입력하세요 (1~5): ");
            scanf("%d", &diary.rating);

            addDiary(diary);
            printf("일기가 저장되었습니다.\n");
            break;

        case 2:
            printf("조회할 날짜를 입력하세요 (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            viewDiary(diary.date);
            break;

        case 3:
            printf("조회할 날짜를 입력하세요 (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            int totalRating = calculateTotalRating(diary.date);
            printf("%s의 일기 총점: %d\n", diary.date, totalRating);
            break;
           
        case 4:
            clearAllDiaries();
            break;

        case 5:
            printf("삭제할 날짜를 입력하세요 (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            deleteDiaryByDate(diary.date);
            break;

        case 6:
            printf("프로그램을 종료합니다.\n");
            break;

        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
        }
    } while (choice != 6);

    return 0;
}
