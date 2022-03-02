#include "pch.h"
#include "Board.h"
#include "ConsoleHelper.h"
#include "Player.h"

const char* TILE = "■";

Board::Board()
{

}
Board::~Board()
{

}
void Board::Init(int32 size, Player* player)
{
    _size = size;
    _player = player;
    GenerateMap();
}

void Board::Render()
{
    ConsoleHelper::SetCursorPosition(0, 0);
    ConsoleHelper::ShowConsoleCursur(false);
    ConsoleHelper::SetCursorColor(ConsoleColor::RED);


    for (int32 y = 0; y < 25; y++)
    {
        for (int32 x = 0; x < 25; x++)
        {
            ConsoleColor color = GetTileColor(Pos{ y, x });
            ConsoleHelper::SetCursorColor(color);
            cout << TILE;
        }
        cout << endl;
    }
}

// Binary Tree 미로 생성 알고리즘
// - Mazes from programmers
void Board::GenerateMap()
{
    // 외곽을 벽으로 만들고 나머지는 비워내는 로직
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            if (x %2 == 0 || y % 2 == 0)
                _tile[y][x] = TileType::WALL;
            else
                _tile[y][x] = TileType::EMPTY;
        }
    }
    
    // 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
    for (int32 y = 0; y < _size; y++)
    {
        for (int32 x = 0; x < _size; x++)
        {
            // 벽은 건드리면 안되기 때문에 continue
            if (x % 2 == 0 || y % 2 == 0)
                continue;

            // 마지막 벽에 있는 점 벽으로... 생성
            if (y == _size - 2 && x == _size - 2)
                continue;
            
            // y축에서 두 번째 줄은 비워준다!
            if (y == _size - 2)
            {
                _tile[y][x + 1] = TileType::EMPTY;
                continue;
            }
            // x축에서 두 번째 줄은 비워준다!
            if (x == _size - 2)
            {
                _tile[y + 1][x] = TileType::EMPTY;
                continue;
            }

            // 랜덤으로 타일을 비워준다!
            const int32 randValue = ::rand() % 2;
            if (randValue == 0)
            {
                _tile[y][x + 1] = TileType::EMPTY;
            }
            else
            {
                _tile[y + 1][x] = TileType::EMPTY;
            }
        }
    }
}

TileType Board::GetTileType(Pos pos)
{
    if (pos.x < 0 || pos.x >= _size)
        return TileType::NONE;

    if (pos.y < 0 || pos.y >= _size)
        return TileType::NONE;

    return _tile[pos.y][pos.x];
}

ConsoleColor Board::GetTileColor(Pos pos)
{
    if (_player && _player->GetPos() == pos)
        return ConsoleColor::YELLOW;

    if (GetExitPos() == pos)
        return ConsoleColor::BLUE;

    TileType tileType = GetTileType(pos);

    switch (tileType)
    {
    case TileType::EMPTY:
            return ConsoleColor::GREEN;
    case TileType::WALL:
        return ConsoleColor::RED;
    }

    return ConsoleColor::WHITE;
}
