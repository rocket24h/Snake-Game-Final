#pragma warning(disable:4068)
#include <iostream>
#include "levels.h"
#include "main_functions.h"
#include <ctime>
#include <conio.h>
#include <thread>
#include <iomanip>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
using namespace std;

extern int levelscore[];
extern unsigned char vborder, hborder, lowerleft, lowerright, upperleft, upperright;

void levelup()
{
    int  r; double q;
    PlaySound("LevelUp.wav", NULL, SND_ASYNC); // Animation cho qua màn 
    for (int i = 0; i < SIZE_SNAKE - 1; i++) {
        GotoXY(snake[i].x, snake[i].y);
        for (q = 0; q <= 20000000; q++);
        printf("%c", ' ');
    }
    GotoXY(36, 14);
    printf("LEVEL UP...");

    if (level < 4) level++;
    else
    {
        level = 999;
    }
    FOOD_INDEX = 8;
    foodcount = 8;
    MOVING = 0;
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        snake[i] = { 40 + i, 10 };
    }
    SPEED++;
}

void drawgate(int a, int b)
{
    cout << CYAN;

    GotoXY(a - 3, b - 1);
    for (int i = 0; i <= 3; i++)
    {
        cout << "#";
    }
    GotoXY(a, b);
    cout << "#";
    GotoXY(a - 3, b + 1);//levelup

    for (int i = 0; i <= 3; i++)
    {
        cout << "#";
    }
}
void touchgate180(int a, int b)
{
    if (MOVING == 'A' && snake[SIZE_SNAKE - 1].x == a && snake[SIZE_SNAKE - 1].y == b && STATE != 0)
    {
        ProcessDead();
        return;
    }
    for (int i = a - 3; i <= a && STATE != 0; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == i && snake[SIZE_SNAKE - 1].y == b - 1)
        {
            ProcessDead();
            break;
        }
        if (snake[SIZE_SNAKE - 1].x == i && snake[SIZE_SNAKE - 1].y == b + 1)
        {
            ProcessDead();
            break;
        }
    }

}

void passlevel(int x, int y)
{
    if (snake[SIZE_SNAKE - 1].x == x && snake[SIZE_SNAKE - 1].y == y)
    {
        levelup();
        system("CLS");
        DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
        /*
        if (level == 2) {
            drawappear();
        }
        else if (level == 3) {
            drawimpediment();
        }
        */
        DrawSnakeAndFood();
        return;
    }
}

void touchimpediment()
{
    for (int i = 0; i < SIZE_SNAKE && STATE != 0; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == impe[i].x && snake[SIZE_SNAKE - 1].y == impe[i].y && score < levelscore[level - 1])
        {
            ProcessDead();
            return;
        }
    }
}
bool existfood(int x, int y)
{

    if (food[SIZE_SNAKE - 1].x == x && food[SIZE_SNAKE - 1].y == y) {
        return false;
    }

    return true;
}
void drawimpediment()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    int x, y;
    srand(time_t(NULL));
    for (int i = 0; i < SIZE_SNAKE; i++) {
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGHT_CONSOLE - 1) + 1;
        } while (IsValid(x, y) == false && existfood(x, y) == false);
        impe[i] = { x,y };
        GotoXY(x, y);
        printf("%c", 'x');
    }

}


void drawappear()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    GotoXY(10, 4);
    cout << "X";
    appear[0].x = 10;
    appear[0].y = 4;
    int d = 1;
    for (int i = 11; i < 70; i++)
    {
        cout << "X";
        appear[d].x = i;
        appear[d].y = 4;
        d++;
    }

    GotoXY(10, 16);
    cout << "X";
    appear[d].x = 10;
    appear[d].y = 16;
    d++;
    for (int i = 11; i < 70; i++)
    {
        cout << "X";
        appear[d].x = i;
        appear[d].y = 16;
        d++;
    }

    for (int i = 5; i < 15; i++)
    {
        GotoXY(4, i);
        cout << "X";
        appear[d].x = 4;
        appear[d].y = i;
        d++;
    }

    for (int i = 5; i < 15; i++)
    {
        GotoXY(75, i);
        cout << "X";
        appear[d].x = 75;
        appear[d].y = i;
        d++;
    }

}

bool existappear(int x, int y)
{
    for (int i = 0; i < 140; i++)
    {
        if (x == appear[i].x && y == appear[i].y) {
            return false;
        }
    }

    return true;
}
void touchappear()
{
    for (int i = 0; i < 140 && STATE != 0; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == appear[i].x && snake[SIZE_SNAKE - 1].y == appear[i].y)
        {
            ProcessDead();
            return;
        }
    }
}


void drawu()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    int d = 0;
    for (int i = 6; i < 16; i++)
    {
        GotoXY(11, i);
        cout << "X";
        u[d].x = 11;
        u[d].y = i;
        d++;
    }
    for (int i = 6; i < 16; i++)
    {
        GotoXY(70, i);
        cout << "X";
        u[d].x = 70;
        u[d].y = i;
        d++;
    }
    for (int i = 6; i < 14; i++)
    {
        GotoXY(15, i);
        cout << "X";
        u[d].x = 15;
        u[d].y = i;
        d++;
    }
    for (int i = 6; i < 14; i++)
    {
        GotoXY(65, i);
        cout << "X";
        u[d].x = 65;
        u[d].y = i;
        d++;
    }
    GotoXY(16, 13);
    cout << "X";
    u[d].x = 16;
    u[d].y = 13;
    d++;
    for (int i = 17; i < 65; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 13;
        d++;
    }
    GotoXY(12, 15);
    cout << "X";
    u[d].x = 12;
    u[d].y = 15;
    d++;
    for (int i = 13; i < 70; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 15;
        d++;
    }

    /// /////////////

    GotoXY(2, 2);
    cout << "X";
    u[d].x = 2;
    u[d].y = 2;
    d++;
    for (int i = 3; i < 6; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 2;
        d++;
    }
    GotoXY(2, 3);
    cout << "X";
    u[d].x = 2;
    u[d].y = 3;
    d++;
    GotoXY(2, 4);
    cout << "X";
    u[d].x = 2;
    u[d].y = 4;
    d++;

    //

    GotoXY(75, 2);
    cout << "X";
    u[d].x = 75;
    u[d].y = 2;
    d++;
    for (int i = 76; i < 79; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 2;
        d++;
    }

    GotoXY(78, 3);
    cout << "X";
    u[d].x = 78;
    u[d].y = 3;
    d++;
    GotoXY(78, 4);
    cout << "X";
    u[d].x = 78;
    u[d].y = 4;
    d++;

    //
    GotoXY(2, 16);
    cout << "X";
    u[d].x = 2;
    u[d].y = 16;
    d++;
    GotoXY(2, 17);
    cout << "X";
    u[d].x = 2;
    u[d].y = 17;
    d++;
    GotoXY(2, 18);
    cout << "X";
    u[d].x = 2;
    u[d].y = 18;
    d++;
    for (int i = 3; i < 6; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 18;
        d++;
    }
    GotoXY(78, 16);
    cout << "X";
    u[d].x = 78;
    u[d].y = 16;
    d++;
    GotoXY(78, 17);
    cout << "X";
    u[d].x = 78;
    u[d].y = 17;
    d++;
    GotoXY(75, 18);
    cout << "X";
    u[d].x = 75;
    u[d].y = 18;
    d++;
    for (int i = 76; i < 79; i++)
    {
        cout << "X";
        u[d].x = i;
        u[d].y = 18;
        d++;
    }



}
void touchu()
{
    for (int i = 0; i < 167 && STATE != 0; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == u[i].x && snake[SIZE_SNAKE - 1].y == u[i].y)
        {
            ProcessDead();
            return;
        }
    }
}
void drawktlt()
{
    int d = 0;
    //chu K
    for (int i = 6; i < 16; i++)
    {
        GotoXY(10, i);
        cout << "X";
        ktlt[d].x = 10;
        ktlt[d].y = i;
        d++;
    }

    for (int i = 15; i > 10; i--)
    {
        GotoXY(i, 21 - i);
        cout << "X";
        ktlt[d].x = i;
        ktlt[d].y = 22 - i;
        d++;
    }
    for (int i = 11; i < 16; i++)
    {
        GotoXY(i, i);
        cout << "X";
        ktlt[d].x = i;
        ktlt[d].y = i;
        d++;
    }
    //Chu T
    GotoXY(25, 6);
    cout << "X";
    ktlt[d].x = 25;
    ktlt[d].y = 6;
    d++;
    for (int i = 26; i < 36; i++)
    {
        cout << "X";
        ktlt[d].x = i;
        ktlt[d].y = 6;
        d++;
    }
    for (int i = 6; i < 16; i++)
    {
        GotoXY(30, i);
        cout << "X";
        ktlt[d].x = 30;
        ktlt[d].y = i;
        d++;
    }
    //chu L
    for (int i = 6; i < 16; i++)
    {
        GotoXY(45, i);
        cout << "X";
        ktlt[d].x = 45;
        ktlt[d].y = i;
        d++;
    }
    GotoXY(46, 15);
    cout << "X";
    ktlt[d].x = 46;
    ktlt[d].y = 15;
    d++;
    for (int i = 47; i < 56; i++)
    {
        cout << "X";
        ktlt[d].x = i;
        ktlt[d].y = 15;
        d++;
    }
    //Chu T
    GotoXY(65, 6);
    cout << "X";
    ktlt[d].x = 65;
    ktlt[d].y = 6;
    d++;
    for (int i = 66; i < 76; i++)
    {
        cout << "X";
        ktlt[d].x = i;
        ktlt[d].y = 6;
        d++;
    }
    for (int i = 6; i < 16; i++)
    {
        GotoXY(70, i);
        cout << "X";
        ktlt[d].x = 70;
        ktlt[d].y = i;
        d++;
    }

}
void touchktlt()
{
    for (int i = 0; i < 82 && STATE != 0; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == ktlt[i].x && snake[SIZE_SNAKE - 1].y == ktlt[i].y)
        {
            ProcessDead();
            return;
        }
    }
}

