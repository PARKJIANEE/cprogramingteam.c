# define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Diary {
    char date[12];
    char mood[20];
    char content[200];
    int rating;  // 1���� 5������ ����
};

void addDiary(struct Diary diary) {
    FILE* file = fopen("diary.txt", "a");
    if (file == NULL) {
        printf("�ϱ� ������ �� �� �����ϴ�.\n");
        exit(1);
    }

    fprintf(file, "%s %s %s %d\n", diary.date, diary.mood, diary.content, diary.rating);

    fclose(file);
}

void viewDiary(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("�ϱ� ������ �� �� �����ϴ�.\n");
        exit(1);
    }

    struct Diary diary;
    int found = 0;

    while (fscanf(file, "%s %s %[^\n] %d", diary.date, diary.mood, diary.content, &diary.rating) != EOF) {
        if (strcmp(diary.date, date) == 0) {
            char* colorCode = "";
            if (strcmp(diary.mood, "���") == 0) {
                colorCode = "\033[1;33m"; // �����
            }
            else if (strcmp(diary.mood, "����") == 0) {
                colorCode = "\033[1;34m"; // �Ķ���
            }
            else if (strcmp(diary.mood, "��ĥ") == 0) {
                colorCode = "\033[1;32m"; // �ʷϻ�
            }
            else if (strcmp(diary.mood, "ȭ��") == 0) {
                colorCode = "\033[1;31m"; // ������
            }
            else if (strcmp(diary.mood, "�ҽ�") == 0) {
                colorCode = "\033[1;35m"; // �����
            }

            printf("%s", colorCode);
            printf("=== %s�� �ϱ� ===\n", date);
            printf("���: %s\n", diary.mood);
            printf("����: %s\n", diary.content);

            // ������ ���� ���� ���
            printf("����: ");
            for (int i = 0; i < diary.rating; ++i) {
                printf("��");
            }
            printf("\n");

            printf("==================\n");

            // ������ �������� ����
            printf("\033[0m");
            found = 1;
        }
    }

    if (!found) {
        printf("%s�� �ϱⰡ �����ϴ�.\n", date);
    }

    fclose(file);
}

int calculateTotalRating(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("�ϱ� ������ �� �� �����ϴ�.\n");
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
        printf("�ϱ� ������ �� �� �����ϴ�.\n");
        exit(1);
    }
    fclose(file);
}

void clearAllDiaries() {
    printf("��� �ϱ⸦ �����Ͻðڽ��ϱ�? (1: ��, 2: �ƴϿ�): ");
    int clearChoice;
    scanf("%d", &clearChoice);
    if (clearChoice == 1) {
        clearDiaryFile();
        printf("��� �ϱⰡ �����Ǿ����ϴ�.\n");
    }
    else {
        printf("�ϱ� ������ ����߽��ϴ�.\n");
    }
}

void deleteDiaryByDate(char date[]) {
    FILE* file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("�ϱ� ������ �� �� �����ϴ�.\n");
        exit(1);
    }

    FILE* tempFile = fopen("temp_diary.txt", "w");
    if (tempFile == NULL) {
        printf("�ϱ� �ӽ� ������ �� �� �����ϴ�.\n");
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
        printf("%s�� �ϱⰡ �����Ǿ����ϴ�.\n", date);
    }
    else {
        printf("%s�� �ϱⰡ �����ϴ�.\n", date);
    }
}

void printMenu() {
    printf("=== �޴� ===\n");
    printf("1. �ϱ� ����\n");
    printf("2. Ư�� ��¥�� �ϱ� ����\n");
    printf("3. ��¥�� ���� Ȯ��\n");
    printf("4. ��� �ϱ� �ʱ�ȭ\n");
    printf("5. Ư�� ��¥�� �ϱ� ����\n");
    printf("6. ���α׷� ����\n");
    printf("============\n");
    printf("�޴��� �����ϼ���: ");
}

int main() {
    int choice;
    struct Diary diary;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("������ ��¥�� �Է��ϼ��� (YYYY.MM.DD): ");
            scanf("%s", diary.date);

            printf("����� �����ϼ��� (���, ����, ��ĥ, ȭ��, �ҽ� ��): ");
            scanf("%s", diary.mood);

            printf("�� �� �������� ������ �ϱ⸦ �ۼ��ϼ���: ");
            getchar();  // ���� ����
            fgets(diary.content, sizeof(diary.content), stdin);

            printf("������ �Է��ϼ��� (1~5): ");
            scanf("%d", &diary.rating);

            addDiary(diary);
            printf("�ϱⰡ ����Ǿ����ϴ�.\n");
            break;

        case 2:
            printf("��ȸ�� ��¥�� �Է��ϼ��� (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            viewDiary(diary.date);
            break;

        case 3:
            printf("��ȸ�� ��¥�� �Է��ϼ��� (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            int totalRating = calculateTotalRating(diary.date);
            printf("%s�� �ϱ� ����: %d\n", diary.date, totalRating);
            break;
           
        case 4:
            clearAllDiaries();
            break;

        case 5:
            printf("������ ��¥�� �Է��ϼ��� (YYYY.MM.DD): ");
            scanf("%s", diary.date);
            deleteDiaryByDate(diary.date);
            break;

        case 6:
            printf("���α׷��� �����մϴ�.\n");
            break;

        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �����ϼ���.\n");
        }
    } while (choice != 6);

    return 0;
}
