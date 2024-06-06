#pragma once
#include"BasePlant.h"



//ÏòÈÕ¿û
class SunFlower :public BasePlant
{
	Animation idle;
	Timer ProduceTimerHandle;

	float transitionLevel = 0.f;
	int state = 0;
public:
	SunFlower();
	
	void Update();

	void Produce();
};