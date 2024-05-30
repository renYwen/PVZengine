#pragma once
#include"Sprite.h"


//�ӵ�����
class BaseBullet :public Sprite
{
protected:
	SpriteRenderer* renderer;
	class CircleCollider* circle;
	
	int damage = 1;
public:
	BaseBullet();
	virtual void BeginPlay();

	virtual void OnOverlap(Collider* overlapComp, Collider* otherComp, Object* otherActor);
};