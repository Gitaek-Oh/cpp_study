#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;

int Player::PlayerTurn()
{
	int PlayerChoice = 0;

	while (true)
	{
		cout << "-------------------------------------------------" << endl;
		cout << "1.공격		2.스킬		3.도망(10%)" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "행동을 선택하세요: ";
		cin >> PlayerChoice;
		if (0 < PlayerChoice && PlayerChoice < 5)
			break;
	}

	return PlayerChoice+1; // enum 잘못된 설정으로 1을 더해준다....;;;
}

void Player::PrintPlayerStatus()
{
	cout << "-------------------------------------------------" << endl;
	cout << "[플레이어]" << endl;
	cout << "체력: " << _hp << endl;
	cout << "마력: " << _player_mp << endl;
	cout << "공격력: " << _attack << endl;
	cout << "방어력: " << _defence << endl;
	cout << "-------------------------------------------------" << endl;
}
int Player::SkillAttack()
{
	int input = 0;
	int damage = 0;

	while (true)
	{
		if (Player_playerType == PT_KNIGHT)
		{
			cout << "-------------------------------------------------" << endl;
			cout << "1.방패공격			2.방패던지기" << endl;
			cout << "-------------------------------------------------" << endl;
		}
		else if (Player_playerType == PT_MAGE)
		{
			cout << "-------------------------------------------------" << endl;
			cout << "1.파이어볼			2.운석소환" << endl;
			cout << "-------------------------------------------------" << endl;
		}
		cout << "스킬을 선택해주세요: ";
		cin >> input;
		if (input == 1 || input == 2)
			break;
	}

	cout << "스킬공격!!!!!" << endl;
	if (input == 1)
	{
		if (_player_mp < 10)
		{
			cout << "마나가 부족합니다!!! 마나가 부족하여 일반공격을 실행합니다." << endl;
			damage = _attack;
		}
		else
		{
			damage = _attack * 2;
			_player_mp -= 10;
		}

	}
	else if (input == 2)
	{
		if (_player_mp < 20)
		{
			cout << "마나가 부족합니다!!! 마나가 부족하여 일반공격을 실행합니다." << endl;
			damage = _attack;
		}
		else
		{
			damage = _attack * 3;
			_player_mp -= 20;
		}
	}

	return damage;
}