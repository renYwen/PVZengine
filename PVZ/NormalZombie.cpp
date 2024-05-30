#include "NormalZombie.h"


NormalZombie::NormalZombie()
{
	walk.Load("normalwalk");
	walk.SetInterval(0.05f);

	ani->Insert("walk", walk);
	ani->SetNode("walk");
}

