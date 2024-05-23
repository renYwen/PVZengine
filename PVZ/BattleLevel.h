#pragma once
#include"CoreMinimal.h"


class BattleLevel :public Level
{
	class Sprite* background0;

public:
	BattleLevel();
	void Update()override;
};