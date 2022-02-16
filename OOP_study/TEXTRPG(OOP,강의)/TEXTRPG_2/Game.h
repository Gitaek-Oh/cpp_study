#pragma once

/*
	Game.h
	- 초기화 함수
	- while의 Update함수
	플레이어와 필드를 불러서 초기화해준다, 필드에는 몬스터가 있다.
*/

// 전방선언... 해당 클래스가 나올 것이라고 미리 정의해준다...?
class Player;
class Field;

class Game
{
public:
	Player* _player;
	Field* _field;

public:
	Game();
	~Game();
	void Update();
	void CreatePlayer();
	void Init();
};