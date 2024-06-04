#pragma once
#include"Sprite.h"
#include"Animator.h"


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

	void TakeDamage(float damage);
};