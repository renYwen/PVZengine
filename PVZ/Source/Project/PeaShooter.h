#pragma once
#include"BasePlant.h"



//�㶹����
class PeaShooter :public BasePlant
{
	AnimationDelegate shootEvent;
	Animation idle;
public:
	PeaShooter();


	void Shoot();
};