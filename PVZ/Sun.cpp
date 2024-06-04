#include "Sun.h"
#include"Collider.h"
#include"RigidBody.h"
#include"Math.h"


Sun::Sun()
{
	renderer = GetComponentByClass<SpriteRenderer>();
	renderer->SetLayer(10);
	animator = ConstructComponent<Animator>();
	ani.Load("sunshine_1");
	ani.SetInterval(0.08f);

	animator->Insert("idle", ani);
	animator->SetNode("idle");

	collider = ConstructComponent<CircleCollider>();
	collider->AttachTo(root);
	collider->SetRadius(35);
	/*collider->SetType(CollisionType::Sunshine);*/

	rigidbody = ConstructComponent<RigidBody>();
	rigidbody->SetGraivty(350.f);
	
	groundLine = Math::RandInt(100,500);

	DestroyTimerHandle.Bind(10, [this]() {bFading = true; });
}

void Sun::Update()
{
	Sprite::Update();

	if (GetWorldPosition().y > groundLine) 
	{ 
		rigidbody->SetGravityEnabled(false); 
		rigidbody->SetMoveable(false);
	}

	if (bFading)
	{
		BYTE tran = renderer->GetTransparency()-5;
		renderer->SetTransparency(tran);
		if (tran <= 5)Destroy();
	}

	if (bGrowing)
	{
		Vector2D scale = GetLocalScale()+Vector2D(1,1)*0.05f;
		if (scale.x >= 1.f) { bGrowing = false; scale = { 1,1 }; }
		SetLocalScale(scale);
	}
}

void Sun::Throw(int groundLine)
{
	rigidbody->AddPulse(Vector2D(Math::RandInt(-40,50),-125));
	this->groundLine = groundLine;
	bGrowing = true;
	SetLocalScale(Vector2D(1,1)*0.1f);
}
