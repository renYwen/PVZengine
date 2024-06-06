#pragma once
#include"Objects/Sprite.h"
#include"Components/Animator.h"


//½©Ê¬»ùÀà
class BaseZombie :public Sprite
{
	enum class ZombieState :uint8
	{
		Walking,Standing
	}state;

protected:
	SpriteRenderer* renderer;
	class BoxCollider* box;
	class Animator* ani;

	float blood = 100;
	float speed = 0.2f;

	Animation walk;
	Animation eat;
	AnimationDelegate dieEvent;
	Animation die;

	std::unordered_set<Actor*>overlapPlants;
	class BasePlant* eatingPlant = nullptr;
public:
	BaseZombie();
	virtual void BeginPlay();
	void Update();

	void GetDamage(float damage);

	virtual void OnOverlap(Collider* overlapComp, Collider* otherComp, Actor* otherActor);
	virtual void EndOverlap(Collider* overlapComp, Collider* otherComp, Actor* otherActor);
};