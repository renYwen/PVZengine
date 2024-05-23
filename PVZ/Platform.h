#pragma once
#include "CoreMinimal.h"
#include "Collider.h"




class Platform : public Object
{
	BoxCollider* collider;


public:
	Platform()
	{
		collider = ConstructComponent<BoxCollider>();
		collider->AttachTo(root);
		collider->SetSize(Vector2D(600, 50));
		collider->SetCollisonMode(CollisionMode::Collision);
		collider->SetType(CollisionType::Platform);
	}

	virtual void Update() override
	{
		Object::Update();
	}
};