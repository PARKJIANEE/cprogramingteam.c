#include <stdio.h>

int main() {
    char answers[] = { 'O', 'X', 'O', 'O', 'X', 'O', 'X', 'X', 'O', 'X' };
    char user_answers[10];
    int score = 0;

    printf("OX ��� �����մϴ�.\n");
    printf("������ ���� ���� O �Ǵ� X�� �Է����ּ���.\n");

    // ���� ��°� ����� �亯 �Է�
    for (int i = 0; i < 10; i++) {
        printf("\n���� %d:\n", i + 1);

        // �� ������ ���� printf�� ����
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

        // ���� Ȯ��
        if (user_answers[i] == answers[i]) {
            printf("�����Դϴ�!\n");
            score++;
        }
        else {
            printf("�����Դϴ�.\n");
        }

        // ���� ����
        while (getchar() != '\n');
    }

    printf("\n���� ����! �� ����: %d / 10\n", score);

    return 0;
}
