#include"NormalZombie.h"
#include"BasePlant.h"

NormalZombie::NormalZombie()
{
	walk.Load("normalwalk");
	walk.SetInterval(0.05f);

	eat.Load("normaleat", {-5,3});
	eat.SetInterval(0.03f);


	ani->Insert("walk", walk);
	ani->Insert("eat", eat);
	ani->SetNode("walk");

	eatEvent.Bind([this]() {if (eatingPlant)eatingPlant->TakeDamage(1.f); });
	eat.AddNotification(10, eatEvent);
	eat.AddNotification(30, eatEvent);
}

