#pragma once
#include "UI/UserInterface.h"



class SeedUI :public UserInterface
{
	Button* button;
public:
	SeedUI();

	void Load(std::string name)
	{
		button->LoadNormalPicture(name);
	}
};