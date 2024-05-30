#include "Pea.h"

Pea::Pea()
{
	renderer->LoadSprite("pea");
}

void Pea::Update()
{
	BaseBullet::Update();

	AddPosition({3,0});
	if (GetWorldPosition().x > 1200)Destroy();
}
