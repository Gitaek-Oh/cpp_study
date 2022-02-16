#include "Game.h"
#include <iostream>
using namespace std;
#include "Player.h"
#include "Field.h"

Game::Game()
{
	// �� Ŭ������ ���� NULL�� �ʱ�ȭ....
	_player = nullptr;
	_field = nullptr;
}

Game::~Game()
{
	// �� Ŭ������ �Ҹ�
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
		cout << "[ĳ���ͼ���] 1) ��� 2) �ü� 3) ������" << endl;
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

