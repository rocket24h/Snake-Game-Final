#ifndef main_functions_h
#define main_functions_h


#pragma once
#include <Windows.h>
#include <string>
#define MAX 1000
extern int foodcount;
extern const char SNAKE_STRUCTURE[33];
extern int maxlength;
extern POINT snake[32]; //snake
extern POINT food[32]; // food
extern int CHAR_LOCK;//used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
extern int MOVING;//used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
extern int SPEED;// Standing for level, the higher the level, the quicker the speed
extern int HEIGHT_CONSOLE, WIDTH_CONSOLE;// Width and height of console-screen
extern int FOOD_INDEX; // current food-index
extern int SIZE_SNAKE; // size of snake, initially maybe 8 units and maximum size may be 32
extern int SIZE_BOSS;
extern int STATE;
extern int BOSS_STATE;
extern int foodtype[32];
extern int level;
extern int score;
extern int BOSS_SCORE;
extern int MAX_SIZE_FOOD;
extern int MAX_SPEED;
extern int BOSS_SPEED;
extern POINT impe[32];
extern POINT u[170];
extern POINT appear[155];
extern POINT boss[32];
extern POINT ktlt[85];


extern std::string filename;

struct diem
{
	int diem;
	char name[200] = { ' ' };
};

void textcolor(char color);
void drawSnek2();
void displayRank(diem list[], int n);
void ranking();
void drawSlogan();
void GenerateFoodType();
void doiCoChu();
void DeleteScrollBar();
void hidecursor();
int foodRandomizer();
void GotoXY(int x, int y);
void FixConsoleWindow();
void load();
bool IsValid(int x, int y);
void GenerateFood();
void ResetData();
void DrawBoard(int x, int y, int width, int height);
void StartGame();
void ExitGame(HANDLE t);
void PauseGame(HANDLE t);
void Eat();
void ProcessDead();
void Touch();
void DrawSnakeAndFood();
void DrawBlankSpace(const char* str);
void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();
void ThreadFunc();
void SaveGame(std::string file);
void LoadingGame();// chinh lai tham so chuyen vao
void CreateUser(std::string& file);
int LoadGame(std::string file);
void drawblahblah();
void drawMenu();
int loadFile(char file[50][200]);//
bool checkDuplicate(std::string file);//
std::string displayLoad();//
// 3 ham chinh 
#endif // !main_functions_h