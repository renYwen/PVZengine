#pragma once
#include "UI/UserInterface.h"



class BattleUI :public UserInterface
{
	Image* SeedBank;
	HorizontalPanel* Panel;
public:
	BattleUI();

	void Update();
};