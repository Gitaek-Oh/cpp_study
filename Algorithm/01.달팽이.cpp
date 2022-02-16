
/*
입력값이 4이면
출력은 다음과 같다.

01 02 03 04
12 13 14 05
11 16 15 06
10 09 08 07

위의 출력처럼 달팽이 모양으로 출력된다.
방향은 >,v,<,^ 이다
*/

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 100;
int board[MAX][MAX] = {};
int N, Y = 0;
int X = -1;

enum
{
	DOWN = 1,
	LEFT = 2,
	UP = 3,
	RIGHT = 4
};


void PintBoard()
{
	for (Y = 0; Y < N; Y++)
	{
		for (X = 0; X < N; X++)
		{
			cout << setfill('0') << setw(2) << board[Y][X] << " ";
		}
		cout << endl;
	}

}

int main()
{
	cout << "달팽이 크기(N * N): ";
	cin >> N;
	int C = RIGHT;
	int count = 1;

	while (true)
	{
		if (count > N * N)
			break;
		switch (C)
		{
		case RIGHT:
			C = DOWN; //방향 아래로 수정
			X = X + 1; // 오른쪽으로 한칸
			for (int i = X; i < N; i++)
			{
				if (board[Y][i] != NULL)
				{
					i = i - 1;
					break;
				}
				board[Y][i] = count;
				count++;
				X = i;
			}
			break;

		case DOWN:
			C = LEFT; //방향 왼쪽으로 수정
			Y = Y + 1; //아래로 한칸

			for (int i = Y; i < N; i++)
			{
				if (board[i][X] != NULL)
				{
					i = i - 1;
					break;
				}
				board[i][X] = count;
				count++;
				Y = i;
			}
			break;

		case LEFT:
			C = UP; //방향 위쪽으로 수정
			X = X - 1; //왼쪽으로 한칸

			for (int i = X; i >= 0; i--)
			{
				if (board[Y][i] != NULL)
				{
					i = i - 1;
					break;
				}
				board[Y][i] = count;
				count++;
				X = i;
			}
			break;

		case UP:
			C = RIGHT; //방향 오른쪽으로 수정
			Y = Y - 1; //위로 한칸

			for (int i = Y; i >= 0; i--)
			{
				if (board[i][X] != NULL)
				{
					i = i - 1;
					break;
				}
				board[i][X] = count;
				count++;
				Y = i;
			}
			break;

		}

	}
	PintBoard();

	return 0;
}
