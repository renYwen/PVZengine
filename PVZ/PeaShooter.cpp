#include "PeaShooter.h"
#include"GameStatics.h"
#include"Pea.h"



PeaShooter::PeaShooter()
{
	idle.Load("peashooter");
	idle.SetInterval(0.06f);
	ani->Insert("idle",idle);
	ani->SetNode("idle");

	shootEvent.Bind(this,&PeaShooter::Shoot);
	idle.AddNotification(11,shootEvent);
}

void PeaShooter::Shoot()
{
	GameStatics::CreateObject<Pea>(GetWorldPosition()+Vector2D(20,-25));
}
