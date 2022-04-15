#pragma warning(disable:4068)
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <thread>
#include <fcntl.h>
#include <io.h>
#include <ColorDlg.h>
#include "levels.h"
#include "main_functions.h"
#define MAX_SIZE_SNAKE 32
#define MAX_SIZE_FOOD 32
#define MAX_SPEED 24
using namespace std;

int foodcount = 8;
const char SNAKE_STRUCTURE[33] = "78672112506721124277211217472112";
int maxlength = sizeof(SNAKE_STRUCTURE) / sizeof(SNAKE_STRUCTURE[0]);
POINT impe[32];
POINT appear[155];
POINT snake[32]; //snake
POINT boss[32];
POINT food[32]; // food
POINT u[170];
POINT ktlt[85];
int totalscore;
int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
int SPEED;// Standing for level, the higher the level, the quicker the speed
int HEIGHT_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 8 units and maximum size may be 32
int SIZE_BOSS;
int STATE;
int BOSS_STATE;
int foodtype[32] = { 0 };
int level = -1;
int score = 0;
int BOSS_SCORE = 0;
int BOSS_SPEED;
//int levelscore[] = { 350, 100, 150, 200 };
int levelscore[] = { 50, 60, 70, 80};
char RIGHT = 'D', LEFT = 'A', UP = 'W', DOWN = 'S';
string filename;


void maingame()
{
    hidecursor();
    int temp;
    thread t1(ThreadFunc);
    HANDLE handle_t1 = t1.native_handle();
    while (1)
    {
        temp = toupper(_getch());
        if (STATE == 1)
        {
            if (temp == 'M')
            {
                this_thread::sleep_for(chrono::milliseconds(1));
                SaveGame(filename);
            }
            if (temp == 'P')
            {
                MOVING = 0;
            }
            else if (temp == 'L') {
                PauseGame(handle_t1);
                int x;
                filename = displayLoad();
                LoadingGame();
                x = LoadGame(filename);
                if (x != 0)
                {
                    system("CLS");
                    break;
                }
                DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
                ResumeThread(handle_t1);
            }
            else if (temp == 27)
            {
                PauseGame(handle_t1);
                ExitGame(handle_t1);
                ResumeThread(handle_t1);
                t1.detach();
                break;
            }
            else
            {
                ResumeThread(handle_t1);
                if ((temp != CHAR_LOCK) && (temp == 'W' || temp == 'A' || temp == 'S' || temp == 'D'))
                {
                    if (temp == RIGHT) CHAR_LOCK = LEFT;
                    else if (temp == UP) CHAR_LOCK = DOWN;
                    else if (temp == DOWN) CHAR_LOCK = UP;
                    else if (temp == LEFT) CHAR_LOCK = RIGHT;
                    MOVING = temp;
                }
            }
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(3050));
            if (temp == 'Y')
            {
                PauseGame(handle_t1);
                StartGame();
                ResumeThread(handle_t1);
            }

            else
            {
                PauseGame(handle_t1);
                t1.detach();
                ExitGame(handle_t1);
                return;
            }
        }
    }
}

int main()
{
    SetConsoleTitle("Snake Souls III");
    //SetConsoleOutputCP(CP_UTF8);
    FixConsoleWindow();
    DeleteScrollBar();
    doiCoChu();
    hidecursor();
    drawblahblah();

    int menu_item = 0, x = 21;
    bool menu = true;
    int flag = 1;
    while (menu)
    {
        drawSnek2();
        drawMenu();
        GotoXY(18 + 25, x);
        cout << "-> ";
        GotoXY(18 + 20 + 25, x);
        cout << " <-";
        GotoXY(25 + 25, 21);
        cout << "Start Game";
        GotoXY(25 + 25, 22);
        cout << "Load Game";
        GotoXY(25 + 25, 23);
        cout << "High Scores";
        GotoXY(25 + 25, 24);
        cout << "Exit Game";

        system("pause>nul"); // the >nul bit causes it the print no message

        if (GetAsyncKeyState(VK_DOWN) && x != 24) // down button pressed
        {
            GotoXY(18 + 25, x);
            cout << "  ";
            GotoXY(18 + 20 + 25, x);
            cout << "  ";
            GotoXY(18 + 21 + 25, x);
            cout << "  ";
            x++;
            GotoXY(18 + 25, x);
            cout << "-> ";
            GotoXY(18 + 20 + 25, x);
            cout << " <-";
            menu_item++;
            continue;
        }

        if (GetAsyncKeyState(VK_UP) && x != 21) // up button pressed
        {
            GotoXY(18 + 25, x);
            cout << "  ";
            GotoXY(18 + 20 + 25, x);
            cout << "  ";
            GotoXY(18 + 21 + 25, x);
            cout << "  ";
            x--;
            GotoXY(18 + 25, x);
            cout << "-> ";
            GotoXY(18 + 20 + 25, x);
            cout << " <-";
            menu_item--;
            continue;
        }

        if (GetAsyncKeyState(VK_RETURN))
        { // Enter key pressed
            switch (menu_item)
            {
            case 0:
            {
                CreateUser(filename);
                PlaySound("Select", NULL, SND_ASYNC);
                StartGame();
                maingame();
                flag = 1;
                level = -1;
                break;
            }

            case 1:
            {
                int x;
                filename = displayLoad();
                LoadingGame();//
                x = LoadGame(filename);
                if (x != 0)
                {
                    system("CLS");
                    break;
                }
                HEIGHT_CONSOLE = 20, WIDTH_CONSOLE = 80;
                DrawBoard(0, 0, WIDTH_CONSOLE, HEIGHT_CONSOLE);
                PlaySound("Select", NULL, SND_ASYNC);
                maingame();
                flag = 1;
                level = -1;
                break;
            }

            case 2:
            {
                //system("cls");
                PlaySound("Select", NULL, SND_ASYNC);
                ranking();
                flag = 1;
                level = -1;
                break;
            }

            case 3:
            {
                menu = false;
                break;
            }

            case 4:
            {
                break;
            }
            }
        }
    }
    return 0;
}




