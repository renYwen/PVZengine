#pragma once
#include"Objects/Sprite.h"
#include"Components/Animator.h"


//ั๔นโ
class Sun : public Sprite
{
	SpriteRenderer* renderer;
	Animation ani;
	Animator* animator;
	class CircleCollider* collider;
	class RigidBody* rigidbody;

	int groundLine;

	Timer DestroyTimerHandle;
	bool bFading = false;
	bool bGrowing = false;
	bool bPicking = false;
public:
	Sun();

	void Update();

	void Fall(int groundLine);

	void Throw(int groundLine);
};