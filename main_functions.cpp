#pragma warning(disable:4068)
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <cwchar>
#include <thread>
#include <string>
#include <string.h>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <condition_variable>
#include <mutex>
#include <io.h>
#include <fstream>
#include <ctime>
#include "main_functions.h"
#include "levels.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define MAX_SIZE_SNAKE 32
#define MAX_SIZE_FOOD 32
#define MAX_SPEED 16
using namespace std;

char fbonus = 254;
unsigned char vborder = 205, hborder = 186, lowerleft = 200, lowerright = 188, upperleft = 201, upperright = 187;
int a = 40;
int b = 6;
extern int levelscore[];
extern char RIGHT, LEFT, UP, DOWN;
extern int totalscore;
extern int colormode;
int bonustype;

void drawSword() {
    int x = 96;
    char raurettrai = 200, rauretphai = 188, mat = 233;
    char cucden = 475, ngang = 461;
    GotoXY(x + 2, 0); cout << raurettrai << mat << " " << mat << rauretphai;
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    GotoXY(x + 2, 1); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x, 2); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 1, 3); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 2, 4); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 3, 5); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 3, 6); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 2, 7); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 1, 8); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x, 9); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x, 10); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 1, 11); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 2, 12); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 3, 13); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 3, 14); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 2, 15); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 1, 16); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x, 17); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x, 18); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 1, 19); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 2, 20); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 3, 21); cout << raurettrai << ngang << cucden << cucden << cucden << ngang << rauretphai;
    GotoXY(x + 4, 22); cout << raurettrai << ngang << cucden << ngang << rauretphai;






}

void textcolor(char color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        color + (__BACKGROUND << 4));
}


void deadAnimation() {
    int flag = 0;
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    printf("%c", ' ');
    for (int i = 0; i < SIZE_SNAKE; i++) {
        GotoXY(snake[i].x, snake[i].y);
        if (flag % 2 != 0) {
            printf("%c", '*');
        }
        else {
            printf("%c", '.');
        }
        for (double x = 0; x < 100000000; x++);
        flag++;

    }
    for (double x = 0; x < 10000000; x++);
}

void doiCoChu()
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void drawMenu()
{
    unsigned char vborder = 205, hborder = 186, lowerleft = 200, lowerright = 188, upperleft = 201, upperright = 187;
    GotoXY(17 + 25, 20);
    for (int i = 0; i < 26; i++)
        cout << vborder;
    GotoXY(16 + 25, 20); cout << upperleft;
    //GotoXY(16 + 25, 20); cout << hborder;
    GotoXY(16 + 25, 21); cout << hborder;
    GotoXY(16 + 25, 22); cout << hborder;
    GotoXY(16 + 25, 23); cout << hborder;
    GotoXY(16 + 25, 24); cout << hborder;
    GotoXY(16 + 25, 25); cout << lowerleft;
    GotoXY(17 + 25, 25);
    for (int i = 0; i < 26; i++)
        cout << vborder;
    GotoXY(16 + 27 + 25, 20); cout << upperright;
    GotoXY(16 + 27 + 25, 21); cout << hborder;
    GotoXY(16 + 27 + 25, 22); cout << hborder;
    GotoXY(16 + 27 + 25, 23); cout << hborder;
    GotoXY(16 + 27 + 25, 24); cout << hborder;
    GotoXY(16 + 27 + 25, 25); cout << lowerright;
}

void drawSnek2() {
    char a = 92;
    int x = 24, mode = 0;

    system("color 70");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 118);
    GotoXY(x, 0); cout << "    Y" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    GotoXY(x, 1); cout << "  .-^-." << endl;
    GotoXY(x, 2); cout << " /     " << a << "      . - ~~- ." << endl;
    GotoXY(x, 3); cout << "()     ()    /   _ _   `.                     _ _ _" << endl;
    GotoXY(x, 4); cout << " " << a << "_   _/    /  /     " << a << "   " << a << "                . ~_ _  ~." << endl;
    GotoXY(x, 5); cout << "   | |     /  /       " << a << "   " << a << "             .' .~       ~-. `." << endl;
    GotoXY(x, 6); cout << "   | |    /  /         )   )           /  /             `.`." << endl;
    GotoXY(x, 7); cout << "   " << a << " " << a << "_ _/  /         /   /           /  /                `'" << endl;
    GotoXY(x, 8); cout << "    " << a << "_ _ _.'         /   /           (  (" << endl;
    GotoXY(x, 9); cout << "                    /   /             " << a << "  " << a << endl;
    GotoXY(x, 10); cout << "                   /   /               " << a << "  " << a << endl;
    GotoXY(x, 11); cout << "                  /   /                 )  )" << endl;
    GotoXY(x, 12); cout << "                 (   (                 /  /" << endl;
    GotoXY(x, 13); cout << "                  `.  `.             .'  /" << endl;
    GotoXY(x, 14); cout << "                    `.   ~ - - - - ~   .'" << endl;
    GotoXY(x, 15); cout << "                       ~ . _ _ _ _ . ~" << endl;
}

void drawblahblah()
{
    system("cls");
    system("color 70");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    for (;;)
    {
        doiCoChu();

        GotoXY(25, 8); cout << "\b\b\b\b\b\b\b\b\b\bLoading   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLOading   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoAding   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoaDing   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadIng   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadiNg   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoadinG   " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading.  " << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading.." << flush;
        Sleep(50);
        cout << "\b\b\b\b\b\b\b\b\b\bLoading..." << flush;
        Sleep(50);
        system("cls");
        GotoXY(25, 8); for (int r = 1; r <= 20; r++)
        {
            for (int q = 0; q <= 100000000; q++);
            printf("%c", 177);
        }
        system("cls");
        GotoXY(26, 8); cout << "PRESS ANY KEY TO CONTINUE";
        cin.get();
        system("cls");
        break;
    }
}

void DeleteScrollBar()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    int Status = SetConsoleScreenBufferSize(hOut, newSize);

    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int foodRandomizer()
{
    srand(time(NULL));
    return rand() % 10 + 1;
}

void GotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void FixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}


void textAnima(char* x) {
    for (int i = 0; x[i] != '\0'; i++) {
        for (double k = 0; k < 20000000; k++);
        printf("%c", x[i]);
    }
}


bool IsValid(int x, int y) {
    for (int i = 0; i < SIZE_SNAKE; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return false;
        }
    }
    return true;
}


void GenerateFood() {
    int x, y;
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGHT_CONSOLE - 1) + 1;
        } while (IsValid(x, y) == false);
        food[i] = { x,y };
    }
}

void GenerateFoodType()
{
    srand(time(NULL));
    for (int i = 0; i < MAX_SIZE_FOOD; i++)
    {
        foodtype[i] = rand() % 5 + 1;
    }
}

void ResetData()
{
    CHAR_LOCK = LEFT, MOVING = RIGHT, SPEED = 8; FOOD_INDEX = 8, WIDTH_CONSOLE = 80, HEIGHT_CONSOLE = 20, SIZE_SNAKE = 8, foodcount = 8, score = 0;
    snake[0] = { 10, 5 }; snake[1] = { 11, 5 };
    snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
    snake[4] = { 14, 5 }; snake[5] = { 15, 5 };
    snake[6] = { 16, 5 }; snake[7] = { 17, 5 };
    snake[8] = { 18, 5 };
    GenerateFood();
    GenerateFoodType();
}

void drawInstructions()
{
    system("color 70");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 114);
    GotoXY(30, 22);
    cout << "GAME INSTRUCTIONS";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    if (level == 1)
    {
        GotoXY(1, 23);
        cout << "Press \"P\" to pause your game";
        GotoXY(1, 25);
        cout << "Press \"M\" to save your game while you play";
        GotoXY(1, 27);
        cout << "Press \"L\" to load another save (works while you play too!)";
    }
    else if (level == 999)
    {
        system("color 03");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        GotoXY(30, 22);
        cout << "GAME INSTRUCTIONS (?)";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        GotoXY(1, 23);

        cout << "You have reached the end of the game!";

        GotoXY(1, 24);
        cout << "Looks like you no longer need instructions";

        GotoXY(1, 25);
        cout << "This is a bonus round! It's an all you can eat buffet!";

        GotoXY(1, 26);
        cout << "If you can keep up, that is...";
        GotoXY(1, 27);
        cout << "Red food gives you double points, but you have to be quick this time";
    }
    else if (level == 2)
    {
        GotoXY(1, 23);
        cout << "Now that you know how the game works, try to complete this level";
        GotoXY(1, 24);
        cout << "Don't touch the obstacle or you will die";
        GotoXY(1, 25);
        cout << "If you see the food overlapping with the obstacle... it's a feature";
        GotoXY(1, 26);
        cout << "Also red food gives you double points";
    }
    else if (level == 4)
    {
        GotoXY(1, 23);
        cout << "You've made it this far! Congratulations";
        GotoXY(1, 24);
        cout << "Let's bring it up a notch, shall we?";
        GotoXY(1, 25);
        cout << "Every time you eat the food, a bomb will be placed randomly on the map";
        GotoXY(1, 26);
        cout << "Just don't be greedy and eat the bombs as well. Good luck!";
    }
    else
    {
        GotoXY(1, 23);
        cout << "Same rules apply, but we doubt you'd make it through this one";
    }


}

void DrawBoard(int x, int y, int width, int height)
{
    int curPosX = 0, curPosY = 0;
    if (level == 999)
    {
        system("color 03");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    }
    else
    {
        system("color 70");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    }
    drawSword();
    GotoXY(x, y); cout << upperleft;
    for (int i = 1; i < width; i++)
    {
        cout << vborder;
    }
    cout << upperright;
    GotoXY(x, height + y); cout << lowerleft;
    for (int i = 1; i < width; i++)
    {
        cout << vborder;
    }
    cout << lowerright;
    for (int i = y + 1; i < height + y; i++)
    {
        GotoXY(x, i); cout << hborder;
        GotoXY(x + width, i); cout << hborder;
    }
    GotoXY(curPosX, curPosY);

    {
        GotoXY(82, 0); cout << upperleft;
        for (int i = 83; i < 94; i++)
        {
            GotoXY(i, 0); cout << vborder;
        }
        GotoXY(94, 0); cout << upperright;
        for (int i = 1; i < 20; i++)
        {
            GotoXY(94, i); cout << hborder;
        }
        GotoXY(94, 20); cout << lowerright;
        for (int i = 83; i < 94; i++)
        {
            GotoXY(i, 20); cout << vborder;
        }
        GotoXY(82, 20); cout << lowerleft;
        for (int i = 1; i < 20; i++)
        {
            GotoXY(82, i); cout << hborder;
        }


        GotoXY(0, 21); cout << upperleft;
        for (int i = 1; i < 94; i++)
        {
            GotoXY(i, 21); cout << vborder;
            GotoXY(i, 28); cout << vborder;
        }
        GotoXY(94, 21); cout << upperright;
        for (int i = 22; i < 28; i++)
        {
            GotoXY(94, i); cout << hborder;
            GotoXY(0, i); cout << hborder;
        }
        GotoXY(0, 28); cout << lowerleft;
        GotoXY(94, 28); cout << lowerright;
    }
    if (level != -1)
    {
        drawInstructions();
        GotoXY(85, 10);
        cout << "Score: ";
        GotoXY(85, 12);
        cout << "Level: ";
        GotoXY(85, 14);
        cout << "Energy";
        GotoXY(85, 15);
        cout << upperleft;
        for (int i = 86; i < 91; i++)
        {
            cout << vborder;
        }
        cout << upperright;
        GotoXY(85, 16);
        cout << hborder;
        GotoXY(91, 16);
        cout << hborder;
        GotoXY(85, 17);
        cout << lowerleft;
        for (int i = 86; i < 91; i++)
        {
            cout << vborder;
        }
        cout << lowerright;
    }

}

void draws()
{
    GotoXY(87, 5);
    cout << upperleft;
    cout << vborder;
    cout << upperright;
    GotoXY(87, 6);
    cout << hborder;
    cout << "S";
    cout << hborder;
    GotoXY(87, 7); cout << lowerleft;
    cout << vborder;
    cout << lowerright;

}
void drawa()
{
    GotoXY(83, 5);
    cout << upperleft;
    cout << vborder;
    cout << upperright;
    GotoXY(83, 6);
    cout << hborder;
    cout << "A";
    cout << hborder;
    GotoXY(83, 7); cout << lowerleft;
    cout << vborder;
    cout << lowerright;

}
void draww()
{
    GotoXY(87, 1);
    cout << upperleft;
    cout << vborder;
    cout << upperright;
    GotoXY(87, 2); cout << hborder;
    cout << "W";
    cout << hborder;
    GotoXY(87, 3); cout << lowerleft;
    cout << vborder;
    cout << lowerright;
}
void drawd()
{
    GotoXY(91, 5);
    cout << upperleft;
    cout << vborder;
    cout << upperright;
    GotoXY(91, 6);
    cout << hborder;
    cout << "D";
    cout << hborder;
    GotoXY(91, 7); cout << lowerleft;
    cout << vborder;
    cout << lowerright;
    return;
}

void StartGame()
{
    level = 1;
    system("CLS");
    DrawBlankSpace(" ");
    ResetData();
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
    STATE = 1;
}

void ExitGame(HANDLE t)
{
    system("CLS");
    DrawBlankSpace(" ");
    TerminateThread(t, 1);
}

void SaveGame(string file) { 
    ofstream myFile;
    myFile.open(file, ios::out);
    if (myFile.is_open()) {
        myFile << SIZE_SNAKE;
        myFile << " ";
        for (int i = 0; i < SIZE_SNAKE; i++) {
            myFile << snake[i].x;
            myFile << " ";
            myFile << snake[i].y;
            myFile << " ";
        }
        myFile << level;
        myFile << " ";
        myFile << score;
        myFile << " ";
        myFile << FOOD_INDEX;
        myFile << " ";
        myFile << food[FOOD_INDEX].x;
        myFile << " ";
        myFile << food[FOOD_INDEX].y;
        myFile << " ";
        myFile << foodcount;
        myFile << " ";
        myFile << foodtype[FOOD_INDEX];
        myFile << " ";
        myFile << SPEED;
        myFile << endl;
        myFile.close();
    }
    else
    {
        myFile.close();
        cout << "ERORR 404" << endl;
    }
}
void PauseGame(HANDLE t)
{
    SuspendThread(t);
    DrawSnakeAndFood();
}

void Eat() {
    snake[SIZE_SNAKE] = food[FOOD_INDEX];
    if ((foodtype[FOOD_INDEX] == 5 && level != 999) || (bonustype == 10 && level == 999))
    {
        score += 20;
    }
    else
    {
        score += 10;
    }
    if (SPEED == MAX_SPEED)
    {
        PlaySound("Evolution", NULL, SND_ASYNC);
        SIZE_SNAKE = 8;
        SPEED = 8;
        FOOD_INDEX = 8;
        foodcount = 8;
        GenerateFood();
        GenerateFoodType();
    }
    else {
        PlaySound("Chewing", NULL, SND_ASYNC);
        foodcount++;
        FOOD_INDEX++;
        SIZE_SNAKE++;
        if (level != 999) SPEED++;
        else SPEED += 3;
    }
}

void ProcessDead() {
    STATE = 0;
    if (level != 999) {
        PlaySound("death", NULL, SND_ASYNC);
        deadAnimation();
        system("cls");
        DrawBoard(0, 0, 80, 20);// Chạy hiệu hứng chết của rắn 
        GotoXY(36, 8);
        char str[] = "You Died";
        char str2[] = "Press Y to restart or press any keys to exit";
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 116);
        textAnima(str);
        SetConsoleTextAttribute(h, 112);
        GotoXY(18, 9);
        textAnima(str2);
    }
    else {
        PlaySound("win", NULL, SND_ASYNC);
        GotoXY(27, 8);
        char str[] = "YOU HAVE COMPLETED THE GAME!";
        char str2[] = "Press Y to restart or press any keys to exit";
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 4);
        textAnima(str);
        SetConsoleTextAttribute(h, 15);
        GotoXY(18, 9);
        textAnima(str2);
    }
}

void Touch()
{
    for (int i = 0; i < SIZE_SNAKE - 2; i++)
    {
        if (snake[SIZE_SNAKE - 1].x == snake[i].x && snake[SIZE_SNAKE - 1].y == snake[i].y)
        {
            ProcessDead();
            break;
        }
    }
}

void drawmoving()
{
    if (level == 999)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    drawa();
    draww();
    draws();
    drawd();
    if (MOVING == 'A')
    {
        cout << YELLOW;
        drawa();
        return;
    }
    if (MOVING == 'S')
    {
        cout << YELLOW;
        draws();
        return;
    }
    if (MOVING == 'D')
    {
        cout << YELLOW;
        drawd();
        return;
    }
    if (MOVING == 'W')
    {
        cout << YELLOW;
        draww();
        return;
    }
}

void DrawSnakeAndFood()
{
    if (foodtype[FOOD_INDEX] == 5)
    {
        cout << RED;
    }
    else
    {
        cout << BLUE;
    }
    if (score < levelscore[level - 1])
    {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        printf("%c", SNAKE_STRUCTURE[foodcount]);
    }
    cout << GREEN;

    for (int i = 0; i < SIZE_SNAKE - 1; i++)
    {
        GotoXY(snake[i].x, snake[i].y);
        printf("%c", SNAKE_STRUCTURE[i]);
    }

    cout << RED;
    GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
    printf("%c", SNAKE_STRUCTURE[SIZE_SNAKE - 1]);

    drawmoving();

    if (score >= levelscore[level - 1] && level != 999)
    {
        drawgate(a, b);
    }

    GotoXY(91, 10);
    cout << score;
    GotoXY(91, 12);
    if (level != 999) cout << level;

    int i = 0;
    int s = score;

    while (s >= 50)
    {
        s = s - 50;
    }
    while (i <= s / 10 && i < 6)
    {
        if (i != 0)
        {
            GotoXY(85 + i, 16);
            cout << char(219);
        }
        i++;
    }
}

void DrawBlankSpace(const char* str)
{
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    printf(str);
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);
        printf(str);
    }
}

void MoveRight()
{
    if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE)
    {
        if (level != 1)
        {
            ProcessDead();
        }
        else
        {
            for (int i = 0; i < SIZE_SNAKE - 1; i++)
            {
                snake[i].x = snake[i + 1].x;
                snake[i].y = snake[i + 1].y;
            }
            snake[SIZE_SNAKE - 1].x = 1;
        }
    }
    else
    {
        if (level == 1)
        {
            if (score < levelscore[level - 1])
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
                {
                    Eat();
                }
                else if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y && snake[SIZE_SNAKE - 1].x + 2 == WIDTH_CONSOLE && level == 1)
                {
                    Eat();
                    for (int i = 0; i < SIZE_SNAKE - 1; i++)
                    {
                        snake[i].x = snake[i + 1].x;
                        snake[i].y = snake[i + 1].y;
                    }
                    snake[SIZE_SNAKE - 1].x = 1;
                }
            }
        }
        else
        {
            if (score < levelscore[level - 1] || level == 999)
            {
                if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
                    Eat();
                bonustype = foodRandomizer();
            }
        }
        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x++;
    }
}

void MoveLeft()
{
    if (snake[SIZE_SNAKE - 1].x - 1 == 0)
    {
        if (level != 1)
        {
            ProcessDead();
        }
        else
        {
            for (int i = 0; i < SIZE_SNAKE - 1; i++)
            {
                snake[i].x = snake[i + 1].x;
                snake[i].y = snake[i + 1].y;
            }
            snake[SIZE_SNAKE - 1].x = WIDTH_CONSOLE - 1;
        }
    }
    else
    {

        if (level != 1)
        {
            if (score < levelscore[level - 1] || level == 999)
            {
                if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
                {
                    Eat();
                    bonustype = foodRandomizer();
                }
            }
        }

        //if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
        else
        {
            if (score < levelscore[level - 1])
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
                {
                    Eat();
                }
                else if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y && snake[SIZE_SNAKE - 1].x - 2 == 0 && level == 1)
                {
                    Eat();
                    for (int i = 0; i < SIZE_SNAKE - 1; i++)
                    {
                        snake[i].x = snake[i + 1].x;
                        snake[i].y = snake[i + 1].y;
                    }
                    snake[SIZE_SNAKE - 1].x = WIDTH_CONSOLE - 1;
                }
            }

        }

        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].x--;
    }
}

void MoveDown()
{
    if (snake[SIZE_SNAKE - 1].y + 1 == HEIGHT_CONSOLE) {

        if (level != 1)
        {
            ProcessDead();
        }
        else
        {
            for (int i = 0; i < SIZE_SNAKE - 1; i++)
            {
                snake[i].x = snake[i + 1].x;
                snake[i].y = snake[i + 1].y;
            }
            snake[SIZE_SNAKE - 1].y = 1;
        }
    }
    else
    {
        //if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
        if (level != 1)
        {
            if (score < levelscore[level - 1] || level == 999)
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y)
                {
                    Eat();
                    bonustype = foodRandomizer();
                }
            }

        }
        //if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
        else
        {
            if (score < levelscore[level - 1])
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
                    Eat();
                }
                else if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y && snake[SIZE_SNAKE - 1].y + 2 == HEIGHT_CONSOLE && level == 1)
                {
                    Eat();
                    for (int i = 0; i < SIZE_SNAKE - 1; i++)
                    {
                        snake[i].x = snake[i + 1].x;
                        snake[i].y = snake[i + 1].y;
                    }
                    snake[SIZE_SNAKE - 1].y = 1;
                }
            }
        }

        for (int i = 0; i < SIZE_SNAKE - 1; i++) {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y++;
    }
}

void MoveUp()
{
    if (snake[SIZE_SNAKE - 1].y - 1 == 0)
    {
        if (level != 1)
        {
            ProcessDead();
        }
        else
        {
            for (int i = 0; i < SIZE_SNAKE - 1; i++)
            {
                snake[i].x = snake[i + 1].x;
                snake[i].y = snake[i + 1].y;
            }
            snake[SIZE_SNAKE - 1].y = HEIGHT_CONSOLE - 1;
        }
    }
    else
    {
        //if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
        if (level != 1)
        {
            if (score < levelscore[level - 1] || level == 999)
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y)
                {
                    Eat();
                    bonustype = foodRandomizer();
                }
            }
        }
        else
        {
            if (score < levelscore[level - 1])
            {
                if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y)
                {
                    Eat();
                }
                else if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y && snake[SIZE_SNAKE - 1].y - 2 == 0 && level == 1)
                {
                    Eat();
                    for (int i = 0; i < SIZE_SNAKE - 1; i++)
                    {
                        snake[i].x = snake[i + 1].x;
                        snake[i].y = snake[i + 1].y;
                    }
                    snake[SIZE_SNAKE - 1].y = HEIGHT_CONSOLE - 1;
                }
            }

        }

        for (int i = 0; i < SIZE_SNAKE - 1; i++)
        {
            snake[i].x = snake[i + 1].x;
            snake[i].y = snake[i + 1].y;
        }
        snake[SIZE_SNAKE - 1].y--;
    }
}

void drawBonus(char str)
{
    if (bonustype == 10) cout << RED;
    else cout << BLUE;
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
    printf("%c", str);
    char head = 237, left = 60, right = 62;
    cout << RESET;

    for (int i = 0; i < SIZE_SNAKE - 1; i++)
    {
        if (i % 2 == 0)
        {
            GotoXY(snake[i].x, snake[i].y);
            printf("%c", left);
        }

        else
        {
            GotoXY(snake[i].x, snake[i].y);
            printf("%c", right);
        }
    }

    cout << YELLOW;
    GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
    printf("%c", head);

    drawmoving();
    GotoXY(91, 10);
    cout << score;
    GotoXY(91, 12);
    if (level != 999) cout << level;
    else cout << "?";

    if (score >= levelscore[level - 1] && level != 999)
    {
        drawgate(a, b);
    }
}


void ThreadFunc()
{
    while (1)
    {
        if (score >= levelscore[level - 1] && level != 999 && STATE != 0)
        {
            touchgate180(a, b);
            passlevel(a, b);
        }
        if (level == 2) touchappear();
        if (level == 4) touchimpediment();
        if (level == 3) touchu();
        if (STATE != 0)
        {
            Touch();
        }
        if (STATE == 1)
        {
            if (STATE != 0) DrawBlankSpace(" ");
            switch (MOVING)
            {
            case 'A':
                MoveLeft();
                break;
            case 'D':
                MoveRight();
                break;
            case 'W':
                MoveUp();
                break;
            case 'S':
                MoveDown();
                break;
            }
        }
        if (level == 2 && STATE != 0)
        {
            drawappear();
        }
        if (level == 3 && STATE != 0)
        {
            drawu();
        }
        if (level == 4 && STATE != 0)
        {
            drawimpediment();
        }
        if (STATE != 0 && level != 999)
        {
            DrawSnakeAndFood();
        }
        else if (STATE != 0 && level == 999)
        {
            drawBonus(fbonus);
        }
        this_thread::sleep_for(chrono::microseconds(1));
        Sleep(900 / SPEED);
    }
}

void LoadingGame()
{
    system("CLS");
    DrawBlankSpace(" ");
    level = 1;
    SPEED = 8; FOOD_INDEX = 8, WIDTH_CONSOLE = 80, HEIGHT_CONSOLE = 20, SIZE_SNAKE = 8, foodcount = 8;
    score = 0; MOVING = 0;
    //DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
    GenerateFood();
    STATE = 1;
}


int LoadGame(string file)
{
    fstream myFile;
    myFile.open(file, ios::in);
    if (myFile.is_open()) {
        int Num = 0;
        int DoDai = 0;
        int Disk = 0;
        int Cot = -1;
        while (myFile >> Disk) {
            if (Cot == -1) {
                SIZE_SNAKE = Disk;
                Num = SIZE_SNAKE * 2 + 7;
                Cot++;
                continue;
            }
            else if (Cot == Num) {
                SPEED = Disk;
            }
            else if (Cot == Num - 1) {
                foodtype[FOOD_INDEX] = Disk;
            }
            else if (Cot == Num - 2) {
                foodcount = Disk;
            }
            else if (Cot == Num - 3) {
                food[FOOD_INDEX].y = Disk;
            }
            else if (Cot == Num - 4) {
                food[FOOD_INDEX].x = Disk;
            }
            else if (Cot == Num - 5) {
                FOOD_INDEX = Disk;
            }
            else if (Cot == Num - 6) {
                score = Disk;
            }
            else if (Cot == Num - 7) {
                level = Disk;
            }
            else if (Cot == 0 || Cot % 2 == 0) {
                snake[DoDai].x = Disk;

            }
            else {
                snake[DoDai].y = Disk;
                DoDai++;
            }
            Cot++;
        }
        myFile.close();
        return 0;
    }
    else
    {
        myFile.close();
        //system("pause");
        GotoXY(19, 9);
        cout << "Save files do not exist!" << endl;
        GotoXY(19, 10);
        system("pause");
        return -1;
    }
}

void CreateUser(string& file)
{
    GotoXY(0, 28);
    string x;
    int i = 0;
    do {
        if (i == 0) {
            cout << GREEN;
            cout << "Please choose your username: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
            getline(cin, x);

            string t = ".txt";
            file = x + t;
            i++;
        }
        else {
            cout << RED;
            cout << "Username is currently unavailable or is inappropriate! Please choose again: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
            getline(cin, x);
            string t = ".txt";
            file = x + t;
        }
    } while (checkDuplicate(file));
    string List = "List.txt";
    fstream myList;
    myList.open(List, ios::app);
    myList << " ";
    myList << file;
    myList.close();
    StartGame();
    SaveGame(file);

}

int loadFile(char file[50][200]) {
    int n = 0;
    fstream myFile;
    myFile.open("List.txt", ios::in);
    if (myFile.is_open()) {
        char can[200];
        while (myFile >> can) {
            strcpy_s(file[n], strlen(can) + 1, can);
            n++;
        }
    }
    else {
        cout << "Error loading files" << endl;
    }
    myFile.close();
    return n; // so luong cua ten trong file
}

bool checkDuplicate(string file) {
    char list[50][200];
    int n = 0;
    char buffer[200];
    strcpy_s(buffer, file.length() + 1, file.c_str());
    n = loadFile(list);
    for (int i = 0; i < n; i++) {
        if (strncmp(buffer, list[i], strlen(list[i] + 1)) == 0) {
            return true; // co ton tai ten
        }
    }
    return false;
}

string displayLoad() {
    string file;
    char list[50][200];
    int n = 0;
    n = loadFile(list);
    system("CLS");
    WIDTH_CONSOLE = 80; HEIGHT_CONSOLE = 20;
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
    GotoXY(24, 1);
    if (n <= 0)
    {
        //cout << "No save files found \nPress \"Enter\" to return";
        return "";
    }
    else
    {
        cout << "Please type your username: ";
        int x = 5;
        int y = 5;
        string s = ".txt";
        for (int i = 0; i < n; i++) {
            if (y + 1 >= HEIGHT_CONSOLE) {
                x = x + 15;
                y = 5;
                if (x + 1 >= WIDTH_CONSOLE) {
                    break;
                }
            }
            GotoXY(x, y);
            cout << list[i];
            y++;
        }
        GotoXY(51, 1);
        getline(cin, file);
        file = file + s;
        return file;
    }
}

void swap(diem& A, diem& B) {
    diem C = A;
    A = B;
    B = C;
}

void sortScore(diem list[], int n)
{
    if (n <= 1) return;
    for (int i = 0; i <= n - 1; i++)
    {
        if (list[i].diem < list[i + 1].diem) swap(list[i], list[i + 1]);
    }
    n = n - 1;
    sortScore(list, n);
}

void removeFileType(char* str)
{
    int n = strlen(str);
    for (int i = n - 1; i >= n - 4; i--)
    {
        str[i] = str[n];
    }
}

void ranking() {
    int n = 0;
    char filename[50][200];
    diem list[50];
    n = loadFile(filename);
    int key = 0;
    for (int i = 0; i < n; i++) {
        key = i;
        fstream myFile;
        myFile.open(filename[i], ios::in);
        if (myFile.is_open()) {
            strcpy_s(list[i].name, strlen(filename[i]) + 1, filename[i]);
            int Num = 0;
            int Disk = 0;
            int Cot = -1;
            while (myFile >> Disk) {
                if (Cot == -1) {
                    SIZE_SNAKE = Disk;
                    Num = SIZE_SNAKE * 2 + 7;
                    Cot++;
                    continue;
                }
                if (Cot == Num - 6) {
                    list[i].diem = Disk;
                }
                Cot++;
            }
        }
        myFile.close();
    }
    if (n >= 1)
    {
        sortScore(list, n);
    }
    displayRank(list, n);

}

void displayRank(diem list[], int n)
{
    system("CLS");
    WIDTH_CONSOLE = 80; HEIGHT_CONSOLE = 20;
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
    if (n <= 0)
    {
        GotoXY(19, 9);
        cout << "Save files do not exist!" << endl;
        GotoXY(19, 10);
        system("pause");
    }
    else
    {
        GotoXY(30, 2);
        cout << "HIGH SCORES";
        int x = 5;
        int y = 5;
        for (int i = 0; i < n; i++) {
            if (y + 1 >= HEIGHT_CONSOLE) {
                x = x + 20;
                y = 5;
                if (x + 1 >= WIDTH_CONSOLE) {
                    break;
                }
            }
            GotoXY(x, y);
            removeFileType(list[i].name);
            if (i == 0)
            {
                cout << YELLOW << i + 1 << "/ " << list[i].name << ": " << list[i].diem;
            }
            else if (i == 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
                cout << i + 1 << "/ " << list[i].name << ": " << list[i].diem;
            }
            else if (i == 2)
            {
                cout << MAGENTA << i + 1 << "/ " << list[i].name << ": " << list[i].diem;
            }
            else
            {
                cout << CYAN << i + 1 << "/ " << list[i].name << ": " << list[i].diem;
            }
            y++;
        }
    }
    cout << endl;
    cin.get();
    system("cls");
}

