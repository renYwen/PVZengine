#pragma once
#include"BasePlant.h"



//Õ„∂π…‰ ÷
class PeaShooter :public BasePlant
{
	AnimationDelegate shootEvent;
	Animation idle;
public:
	PeaShooter();


	void Shoot();
};