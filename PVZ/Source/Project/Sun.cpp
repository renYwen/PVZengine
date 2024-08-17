#include"Sun.h"
#include"Components/Collider.h"
#include"Components/RigidBody.h"
#include"Tools/Math.h"
#include"GameplayStatics.h"
#include"BattleController.h"


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
	

	rigidbody = ConstructComponent<RigidBody>();
	rigidbody->SetGraivty(400.f);

	groundLine = Math::RandInt(100, 500);

	DestroyTimerHandle.Bind(10, [this]() {bFading = true; });
}


void Sun::Update()
{
	Sprite::Update();

	if (GetWorldPosition().y > groundLine && !bPicking) 
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
		Vector2D scale = GetLocalScale() + Vector2D(1,1)*0.05f;
		if (scale.x >= 1.f) { bGrowing = false; scale = { 1,1 }; }
		SetLocalScale(scale);
	}

	if (bPicking)
	{
		if (BattleController* pController = Cast<BattleController>(GameplayStatics::GetController()))
		{
			if (GetWorldPosition().y > 25)return;
			pController->SetSunshineNum(pController->GetSunshineNum() + 25);
			Destroy();
		}
		return;
	}
	
	if (Controller* pController = GameplayStatics::GetController())
	{
		if (collider->IsMouseOver() && pController->IsMouseClicked())
		{
			bPicking = true;
			bFading = false;
			rigidbody->SetGraivty(false);
			rigidbody->SetMoveable(true);
			rigidbody->SetVelocity((-GetWorldPosition() + Vector2D(25, 25)) * 1.25);
		}
	}
}


void Sun::Fall(int groundLine)
{
	rigidbody->SetGravityEnabled(false);
	this->groundLine = groundLine;
	rigidbody->SetVelocity(Vector2D(0,50));
	DestroyTimerHandle.SetDelay(15);
}

void Sun::Throw(int groundLine)
{
	rigidbody->AddPulse(Vector2D(Math::RandInt(-40,50),-125));
	this->groundLine = groundLine;
	bGrowing = true;
	SetLocalScale(Vector2D(1,1)*0.1f);
}


