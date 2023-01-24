#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool GameOver;
const int width = 20, height = 20;
int x, y;
int score, FoodX, FoodY;
int tailX[100];
int tailY[100];
int nTail;
enum eDiraction { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDiraction dir;


void Setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FoodX = rand() % width;
	FoodY = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0) cout << "#";
			if (j == x && i == y) cout << "O";
			else if (j == FoodX && i == FoodY) cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
			if (j == width - 1) cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x == FoodX && y == FoodY)
	{
		score += 10;
		FoodX = rand() % width;
		FoodY = rand() % height;
		nTail++;
	}

	//if (x < 0 || x > width - 1 || y < 0 || y > height - 1) GameOver = true;

	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			GameOver = true;
		}
	}

	if (x == 0) x = width;
	if (x > width) x = 0;

	if (y == 0) y = height;
	if (y > height) y = 0;
}



int main()
{
	srand(time(NULL));
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(30);
	}
	return 0;
}