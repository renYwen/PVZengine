#pragma once
#include"Objects/Sprite.h"
#include"Components/Animator.h"


//Ö²Îï»ùÀà
class BasePlant :public Sprite
{
protected:
	SpriteRenderer* renderer;
	class BoxCollider* box;
	class Animator* ani;

	float blood = 10;
	int cost = 0;
public:
	BasePlant();
	virtual void BeginPlay()override;
	void TakeDamage(float damage);
	void Activate();
	int GetCost()const { return cost; }
};