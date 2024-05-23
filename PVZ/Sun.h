#pragma once
#include"Sprite.h"
#include"Animator.h"
#include"Collider.h"
#include"RigidBody.h"




class Sun : public Sprite
{
	Animation ani;
	Animator* animator;
	CircleCollider* collider;
	RigidBody* rigidbody;
public:
	Sun()
	{
		SpriteRenderer* renderer = GetComponentByClass<SpriteRenderer>();
		renderer->SetLayer(10);
		animator = ConstructComponent<Animator>();
		ani.Load("sunshine_1");
		ani.SetInterval(0.06f);

		animator->Insert("idle", ani);
		animator->SetNode("idle");

		collider = ConstructComponent<CircleCollider>();
		collider->AttachTo(root);
		collider->SetRadius(35);
		collider->SetCollisonMode(CollisionMode::Collision);
		collider->SetType(CollisionType::Sunshine);

		rigidbody = ConstructComponent<RigidBody>();

		/*collider->OnComponentBeginOverlap.AddDynamic(this, &Sun::OnOverlap);*/
	/*	collider->OnComponentBeginOverlap.RemoveDynamic(this, &Sun::OnOverlap);*/
	/*	collider->OnComponentHit.AddDynamic(this, &Sun::OnHit);*/
	}

	void OnOverlap(Collider* overlapComp, Collider* otherComp, Object* otherActor)
	{
		std::cout << "SunShine Overlap" << "   :  ";
		std::cout << otherActor->GetName() << std::endl;
	}
	void OnHit(Collider* hitComp, Collider* otherComp, Object* otherActor, Vector2D hitNormal, const HitResult& hitResult)
	{
		if(otherComp->GetType() == CollisionType::Sunshine)return;
		std::cout << "SunShine Hit" << "   :  ";
		std::cout << otherActor->GetName() << std::endl;
	}
};