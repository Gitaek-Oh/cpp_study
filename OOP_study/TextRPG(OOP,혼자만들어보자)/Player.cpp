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
		cout << "1.����		2.��ų		3.����(10%)" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "�ൿ�� �����ϼ���: ";
		cin >> PlayerChoice;
		if (0 < PlayerChoice && PlayerChoice < 5)
			break;
	}

	return PlayerChoice+1; // enum �߸��� �������� 1�� �����ش�....;;;
}

void Player::PrintPlayerStatus()
{
	cout << "-------------------------------------------------" << endl;
	cout << "[�÷��̾�]" << endl;
	cout << "ü��: " << _hp << endl;
	cout << "����: " << _player_mp << endl;
	cout << "���ݷ�: " << _attack << endl;
	cout << "����: " << _defence << endl;
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
			cout << "1.���а���			2.���д�����" << endl;
			cout << "-------------------------------------------------" << endl;
		}
		else if (Player_playerType == PT_MAGE)
		{
			cout << "-------------------------------------------------" << endl;
			cout << "1.���̾			2.���ȯ" << endl;
			cout << "-------------------------------------------------" << endl;
		}
		cout << "��ų�� �������ּ���: ";
		cin >> input;
		if (input == 1 || input == 2)
			break;
	}

	cout << "��ų����!!!!!" << endl;
	if (input == 1)
	{
		if (_player_mp < 10)
		{
			cout << "������ �����մϴ�!!! ������ �����Ͽ� �Ϲݰ����� �����մϴ�." << endl;
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
			cout << "������ �����մϴ�!!! ������ �����Ͽ� �Ϲݰ����� �����մϴ�." << endl;
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