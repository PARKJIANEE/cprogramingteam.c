#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void SetConsoleView() {
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs. By BlockDMask.");
}

void GotoXY(int x, int y) {
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown() {
    if (_kbhit() != 0) {
        return _getch();
    }
    return 0;
}

void DrawDino(int dinoY) {
    GotoXY(0, dinoY);
    static bool legFlag = true;
    printf("         $$$$$$    \n");
    printf("        $$$$$$$$   \n");
    printf("       $ $$$$$$    \n");
    printf("      $   $$$$  $$ \n");
    printf("       $$$$$$$$$   \n");
    printf("     $$  $$$$$     \n");
    printf("        $$$$$$$    \n");
    printf("        $$$$$$$    \n");
    printf("        $$$ $$$    \n");
    printf("        $$$ $$$    \n");
    if (legFlag) {
        printf("        $$   $$$    \n");
        printf("        $$          ");
        legFlag = false;
    }
    else {
        printf("        $$$  $$    \n");
        printf("             $$    ");
        legFlag = true;
    }
}

void DrawTree(int treeX) {
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("    $$");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf("   $  $");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf("  $    $");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf(" $      $");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf("$        $");
}

void DrawGameOver(const int score) {
    system("cls");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);
    printf("===========================");
    GotoXY(x, y + 5);
    printf("SCORE : %d", score);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("종료하려면 'm'을 누르시오 . . .\n");
    printf("or\n");
    system("pause");

}

bool isCollision(const int treeX, const int dinoY) {
    if (treeX <= 8 && treeX >= 4 && dinoY > 8) {
        return true;
    }
    return false;
}

int main() {
    SetConsoleView();

    while (true) {
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        clock_t start, curr;
        start = clock();

        while (true) {
            if (isCollision(treeX, dinoY))
                break;

            int key = GetKeyDown();

            if (key == 'w' && isBottom) {
                isJumping = true;
                isBottom = false;
                score++;
            }

            if (key == 'm') {
                return 0;
            }

            if (isJumping) {
                dinoY -= gravity;
            }
            else {
                dinoY += gravity;
            }

            if (dinoY >= DINO_BOTTOM_Y) {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            treeX -= 2;
            if (treeX <= 0) {
                treeX = TREE_BOTTOM_X;
            }

            if (dinoY <= 3) {
                isJumping = false;
            }

            DrawDino(dinoY);
            DrawTree(treeX);

            Sleep(60);
            system("cls");

            GotoXY(22, 0);
            printf("Score : %d ", score);

            if (key == 'm') {
                system("cls");
                return 0;
            }
        }

        DrawGameOver(score);
    }
    return 0;
}
