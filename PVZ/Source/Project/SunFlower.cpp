#include"SunFlower.h"
#include"GameplayStatics.h"
#include"Sun.h"


SunFlower::SunFlower()
{
	idle.Load("sunflower");
	idle.SetInterval(0.06f);
	ani->Insert("idle", idle);
	ani->SetNode("idle");

	ProduceTimerHandle.Bind(20, [this]() {state = 1; }, true, 7.5);
}

void SunFlower::Update()
{
	BasePlant::Update();

	if (state == 1)
	{
		renderer->SetFilter(true,RGB(255, 245, 140), transitionLevel += 0.4f);
		if (transitionLevel >= 45) 
		{ 
			Produce(); 
			state = 2; 
		}
	}
	else if (state == 2)
	{
		renderer->SetFilter(true, RGB(255, 245, 140), transitionLevel -= 0.3f);
		if (transitionLevel <= 1)
		{
			state = 0; transitionLevel = 0;
			renderer->SetFilter(false);
		}
	}
}

void SunFlower::Produce()
{
	Sun* sunshine = GameplayStatics::CreateObject<Sun>(GetWorldPosition()-Vector2D(10,20));
	if(sunshine)sunshine->Throw(GetWorldPosition().y + 25);
}
