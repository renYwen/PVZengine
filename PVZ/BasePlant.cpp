#include "BasePlant.h"
#include"Collider.h"



BasePlant::BasePlant()
{
	renderer = GetComponentByClass<SpriteRenderer>();
	renderer->SetLayer(1);
	box = ConstructComponent<BoxCollider>();
	box->AttachTo(root);
	box->SetSize({50,70});
	box->SetType(CollisionType::Plant);

	ani = ConstructComponent<Animator>();
}

void BasePlant::TakeDamage(float damage)
{
	blood -= damage;
	Blink(0.2f, WHITE);

	if (blood <= 0)Destroy();
}
