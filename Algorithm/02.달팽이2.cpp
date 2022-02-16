#include <iostream>https://github.com/Gitaek-Oh/cpp_study/actions
#include <iomanip>
using namespace std;

const int MAX = 100;
int board[MAX][MAX] = {};
int N;


enum DIR
{
	RIGHT = 0,
	DOWN,
	LEFT,
	UP,
};


bool CanWego(int Y, int X)
{
	if (Y < 0 || Y >= N)
		return false;
	else if (X < 0 || X >= N)
		return false;
	else if (board[Y][X] != NULL)
		return false;
	else
		return true;
}


void PintBoard()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << setfill('0') << setw(2) << board[i][j] << " ";
		}
		cout << endl;
	}
}


void StartBoard()
{
	int Dir = RIGHT;
	int Count = 1;

	int Y = 0;
	int X = 0;
	int dirY[4] = { 0, 1, 0, -1 };
	int dirX[4] = { 1, 0, -1, 0 };

	while (true)
	{
		board[Y][X] = Count;

		if (Count == N * N) //이거 때문에 1시간 소모함...
			break;

		int nextY = Y + dirY[Dir];
		int nextX = X + dirX[Dir];

		if (CanWego(nextY, nextX))
		{
			Y = nextY;
			X = nextX;
			Count++;
		}
		else
			Dir = (1 + Dir) % 4;

	}
}

int main()
{
	cout << "달팽이 크기(N * N): ";
	cin >> N;

	StartBoard();
	PintBoard();

	return 0;
}
