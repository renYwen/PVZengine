#pragma once
#include "UI/UserInterface.h"



class SeedUI :public UserInterface
{
	Button* button;

	std::string name{};

	int price = 0;

	int number = 0;
public:
	SeedUI();

	void Init(int num);

	virtual void Update()override;
};