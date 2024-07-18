#pragma once
#include "UI/UserInterface.h"
#include "Tools/Timer.h"


class SeedUI :public UserInterface
{
	Button* button;

	Image* gray;

	Image* black;

	int number = 0;

	Timer CoolingTimerHandle;
public:
	SeedUI();

	void Init(int num);

	virtual void Update()override;

	void ReadyToPlant();
};