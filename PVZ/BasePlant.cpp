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
