#include "BaseZombie.h"
#include"Collider.h"


BaseZombie::BaseZombie()
{
	renderer = GetComponentByClass<SpriteRenderer>();
	renderer->SetLayer(1);
	box = ConstructComponent<BoxCollider>();
	box->AttachTo(root);
	box->SetSize({ 40,100 });
	box->SetType(CollisionType::Zombie);

	ani = ConstructComponent<Animator>();


	die.Load("zombiedie",Vector2D(-20, -12));
	die.SetInterval(0.12f);

	ani->Insert("die", die);

	dieEvent.Bind([this]() {this->Destroy(); });
	die.AddNotification(9, dieEvent);
}

void BaseZombie::Update()
{
	Sprite::Update();

	if(blood>0)AddPosition({-speed,0});
}

void BaseZombie::GetDamage(float damage)
{
	blood -= damage;
	Blink(0.2f,WHITE);

	if (blood <= 0)
	{
		ani->SetNode("die");
	}
}
