#pragma once

// ���漱��!!!
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

	void CreatePlayer();
	void Reset();
	void Update();


};

