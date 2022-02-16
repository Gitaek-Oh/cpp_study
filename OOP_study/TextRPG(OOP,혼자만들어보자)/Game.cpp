#include "Game.h"
#include <iostream>
using namespace std;
#include "Player.h"
#include "Field.h"

Game::Game()
{
	_player = nullptr;
	_field = nullptr;
}

Game::~Game()
{
	if (_player == nullptr)
		delete _player;
	if (_field == nullptr)
		delete _field;
}

void Game::CreatePlayer()
{
	while (_player == nullptr)
	{
		int input = 0;
		cout << "-------------------------------------------------" << endl;
		cout << "[0] 기사, [1] 마법사" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "캐릭터를 선택해주세요!!!!";
		cin >> input;
		cout << "-------------------------------------------------" << endl;

		if (input == PT_KNIGHT)
			_player = new Knight();
		else if (input == PT_MAGE)
			_player = new Mage();
	}
}

void Game::Reset()
{
	_field = new Field();
}

void Game::Update()
{
	if (_player == nullptr)
		CreatePlayer();
	
	if (_player->IsDead())
	{
		delete _player;
		_player = nullptr;
		CreatePlayer();
	}

	_field->MonsterUpdate(_player);
}
