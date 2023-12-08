#include <stdio.h>
#include <stdlib.h>

void game1();
void game2();
void game3();
void game4();

int main() {
    int choice;

    do {
        printf("������ �����ϼ���:\n");
        printf("=======================\n");
        printf("1. ��� ���� ����\n");
        printf("2. ���� ����\n");
        printf("3. �ͼ��� ���� ����\n");
        printf("4. ��Ʈ���� ����\n");
        printf("5. ����\n");
        printf("=======================\n");
        printf("����: ");
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
            printf("������ �����մϴ�.\n");
            break;
        default:
            printf("��ȿ���� ���� �Է��Դϴ�. �ٽ� �����ϼ���.\n");
        }
    } while (choice != 5);

    return 0;
}

void game1() {
    char answers[] = { 'O', 'X', 'O', 'O', 'X', 'O', 'X', 'X', 'O', 'X' };
    char user_answers[10];
    int score = 0;

    printf("OX ��� �����մϴ�.\n");
    printf("������ ���� ���� O �Ǵ� X�� �Է����ּ���.\n");

    for (int i = 0; i < 10; i++) {
        printf("\n���� %d:\n", i + 1);

        switch (i) {
        case 0:
            printf("���迡�� ���� ū ����� �ƽþ��̴�. (O/X)\n");
            break;
        case 1:
            printf("�¾�迡�� ������ 3��°�� ����� �༺�̴�. (O/X)\n");
            break;
        case 2:
            printf("���� ȭ�н����� H2O�̴�. (O/X)\n");
            break;
        case 3:
            printf("�������� ������ �ĸ��̴�. (O/X)\n");
            break;
        case 4:
            printf("5+7�� 10�̴�. (O/X)\n");
            break;
        case 5:
            printf("�ΰ��� ������ ��������� 70 ~ 80ȸ �ɹڼ��� ������. (O/X)\n");
            break;
        case 6:
            printf("�״������� ������ �Ͻ��׸����̴�. (O/X)\n");
            break;
        case 7:
            printf("��īȥŸ���� �ִϸ��̼� ��ȭ ���ΰ��̴�. (O/X)\n");
            break;
        case 8:
            printf("�������� �Ϸ翡 ���� �� ���̸� �Դ´�. (O/X)\n");
            break;
        case 9:
            printf("�ٴ��� ���� �׻� Ǫ����. (O/X)\n");
            break;
        default:
            break;
        }

        printf("O �Ǵ� X �Է�: ");
        scanf(" %c", &user_answers[i]);

        if (user_answers[i] == answers[i]) {
            printf("�����Դϴ�!\n");
            score++;
        }
        else {
            printf("�����Դϴ�.\n");
        }

        while (getchar() != '\n');
    }

    printf("\n���� ����! �� ����: %d / 10\n", score);
}

void game2() {
    printf("���� 2 ����!\n");
}

void game3() {
    printf("���� 3 ����!\n");
}

void game4() {
    printf("���� 4 ����!\n");

}