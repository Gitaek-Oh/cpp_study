#pragma once
/*
	Creature.h (�ֻ��� �θ�?)
	- �÷��̾� ���� ����
	- ��� ���� Ȯ��
	- ���� ��Ȳ
	- ����Ʈ (�����Լ�)
	��.... ����� ����
*/
enum CreatureType
{
	CT_PLAYER = 0,
	CT_MONSTER
};

class Creature
{
protected:
	int _creatureType;
	int _hp = 0;
	int _attack = 0;
	int _defence = 0;

public:
	Creature(int CreatureType) : _creatureType(CreatureType)
	{

	}

	// �ֻ��� �θ� �����Լ��� ���̸�.... 
	// vftable�� �����ڵ��� ���� ������ �����Լ��� �Ҹ�Ǹ� ��� �����ڵ��� �Ҹ�ȴ�?
	// -> �޸� ���� X, �׷��ٸ� �� �����ڴ� �����Լ��� �Ⱥ��̴°�....? ������� �ڴ�....
	virtual ~Creature()
	{

	}

	virtual void PrintInfo() = 0;

	bool IsDead() { return _hp <= 0; }
	void OnAttacked(Creature* attacker);
};