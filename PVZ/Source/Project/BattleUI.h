#pragma once
#include "UI/UserInterface.h"



class BattleUI :public UserInterface
{
	Image* SeedBank;
	HorizontalPanel* Panel;
	Text* SunShine;
public:
	BattleUI();

	void Update();
};