#pragma once
#include"Sprite.h"
#include"Animator.h"


//½©Ê¬»ùÀà
class BaseZombie :public Sprite
{
protected:
	SpriteRenderer* renderer;
	class BoxCollider* box;
	class Animator* ani;

	float blood = 10;
	float speed = 0.2f;

	Animation walk;
	Animation eat;
	AnimationDelegate dieEvent;
	Animation die;
public:
	BaseZombie();
	void Update();

	void GetDamage(float damage);
};