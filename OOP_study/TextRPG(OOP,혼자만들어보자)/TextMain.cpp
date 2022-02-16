#include <iostream>
using namespace std;
#include "Game.h"

/*
흠... 혼자 설계해보자...
1. 캐릭터 선택 1) 기사 2) 마법사
2. 필드입장
3. 몬스터 랜덤 등장 1) 슬라임 2) 오크 3) 스켈레톤
4. 배틀 시작 
	- 플레이어 선공격, 몬스터 후공격
	- 플레이어 1) 공격 2) 스킬(2개, MP필요) 3) 도망가기(확률은 10프로, 실패시 몬스터의 턴)
	- 일반공격 시 25% 확률로 크리티컬 데미지
	- 마나가 부족하면 일반공격으로 대신한다
	- 사망시 Game Over 및 캐릭터 선택으로 돌아감 (격퇴한 몬스터의 종류 및 숫자)
	- 승리시 다음 몬스터 랜덤으로 자동 등장

클래스를 음.... 강의 들었던거랑 비슷하게 해서 만들어 볼까?
*/

int main()
{
	srand((unsigned int)time(nullptr));
	Game game;

	game.Reset();

	while (true)
	{
		game.Update();
	}	
	return 0;
}