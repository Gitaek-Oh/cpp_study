#include "Game.h"
#include <iostream>
using namespace std;
#include "Player.h"
#include "Field.h"

Game::Game()
{
	// 각 클래스의 값을 NULL로 초기화....
	_player = nullptr;
	_field = nullptr;
}

Game::~Game()
{
	// 각 클래스를 소멸
	if (_player != nullptr)
		delete _player;
	if (_field != nullptr)
		delete _field;
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
	_field->Update(_player);
}

void Game::CreatePlayer()
{
	while (_player == nullptr)
	{
		cout << "--------------------------------------" << endl;
		cout << "[캐릭터선택] 1) 기사 2) 궁수 3) 마법사" << endl;
		cout << "--------------------------------------" << endl;
		
		int input = 0;
		cin >> input;

		switch (input)
		{
		case PT_KNIGHT:
			_player = new Knight();
		
		case PT_ARCHER:
			_player = new Archer();
		
		case PT_MAGE:
			_player = new Mage();
		}
	}
}

void Game::Init()
{
	_field = new Field();
}

