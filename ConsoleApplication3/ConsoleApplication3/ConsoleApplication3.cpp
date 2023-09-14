#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;

enum Directions { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
enum Colors { RED = 12, BLACK = 0, DARKBLUE = 3, YELLOW = 14, PINK = 13 };
enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, HEAL = 4 };
int main()
{
	system("title Maze");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.bVisible = 1;
	SetConsoleCursorInfo(h, &info);

	const int width = 60;
	const int height = 25;
	int maze[height][width] = {};

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// GENERATION
			maze[y][x] = rand() % 5;

			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y][x] = 1;

			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 ||
				x == width - 1 && y == height - 3)
				maze[y][x] = 0;

			if (maze[y][x] == 3)
			{
				int probability = rand() % 10;
				if (probability != 0)
				{
					maze[y][x] = 0;
				}
			}
			if (maze[y][x] == 4)
			{
				int probability = rand() % 10;
				if (probability != 0)
				{
					maze[y][x] = 0;
				}
			}

			// COLORWORK
			if (maze[y][x] == HALL)
			{
				SetConsoleTextAttribute(h, BLACK);
				cout << " ";
			}
			else if (maze[y][x] == WALL)
			{
				SetConsoleTextAttribute(h, DARKBLUE);
				cout << (char)178;
			}
			else if (maze[y][x] == COIN)
			{
				SetConsoleTextAttribute(h, YELLOW);
				cout << ".";
			}
			else if (maze[y][x] == ENEMY)
			{
				SetConsoleTextAttribute(h, RED);
				cout << "*";
			}
			else if (maze[y][x] == HEAL)
			{
				SetConsoleTextAttribute(h, RED);
				cout << "I";
			}
			else
			{
				cout << maze[y][x];
			}
		}
		cout << "\n";
	}
	COORD position;
	position.X = 0;
	position.Y = 2;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, PINK);
	cout << "O";

	int coins = 0;
	int HealthPoints = 100;
	int enemyDAMAGE = 25;
	int medkitHEAL = 25;

	while (true)
	{
		// CONTROL
		int code = _getch();
		if (code == 224)
		{
			code = _getch();
		}
		SetConsoleCursorPosition(h, position);
		cout << " ";
		if (code == RIGHT and maze[position.Y][position.X + 1] != 1)
			position.X++;
		if (code == LEFT and maze[position.Y][position.X - 1] != 1)
			position.X--;
		if (code == UP and maze[position.Y - 1][position.X] != 1)
			position.Y--;
		if (code == DOWN and maze[position.Y + 1][position.X] != 1)
			position.Y++;
		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, 13); 
		cout << "O";

		// LABYRINTH COMPLETION

		if (position.X == width - 1 and
			position.Y == height - 3)
		{
			MessageBoxA(0, "Вы прошли лабиринт", "победа", MB_OK);
			break;
		}
		if (maze[position.Y][position.X] == COIN)
		{
			// COIN ADD

			coins++;
			maze[position.Y][position.X] = HALL;
			COORD coins_info;
			coins_info.X = width + 1;
			coins_info.Y = 1;
			SetConsoleCursorPosition(h, coins_info);
			SetConsoleTextAttribute(h, YELLOW);
			cout << "COINS: " << coins;
		}
		if (maze[position.Y][position.X] == ENEMY or maze[position.Y][position.X] == HEAL)
		{
			// HP REMOVE

			if (maze[position.Y][position.X] == ENEMY)
			{
				HealthPoints = HealthPoints - enemyDAMAGE;
				maze[position.Y][position.X] = HALL;
			}
			if (maze[position.Y][position.X] == HEAL)
			{
				HealthPoints = HealthPoints + medkitHEAL;
				maze[position.Y][position.X] = HALL;
				if (HealthPoints > 100)
				{
					HealthPoints = 100;
				}
			}
			COORD HP_info;
			HP_info.X = width + 1;
			HP_info.Y = 2;
			SetConsoleCursorPosition(h, HP_info);
			SetConsoleTextAttribute(h, RED);
			cout << "HP: " << HealthPoints;
			// LOSE SYSTEM
			if (HealthPoints < 05)
			{
				system("cls");
				cout << "lose (your hp is gone)\n\n";
				Sleep(INFINITE);
			}

		}

	}

	system("cls");
	cout << "win\n\n";
	Sleep(INFINITE);
}