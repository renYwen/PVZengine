#pragma once
#include"CoreMinimal.h"



//刚体组件
class RigidBody final:public Component
{
	Vector2D velocity = Vector2D(0,0);
	float maxSpeed = 1000.0f;
	bool bMoveable = true;
    float gravity = 98.f;
	bool bGravityEnabled = true;
	float angularVelocity = 0;
	bool bRotatable = true;
	float mass = 1.0f;

	void RestrictVelocity(Vector2D impactNormal);
public:
	virtual void Update() override;

	void SetGraivty(float gravity) { this->gravity = gravity; }
	void SetVelocity(Vector2D velocity) { this->velocity = velocity; }
	void SetMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
	void SetAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
	void SetMass(float mass) { this->mass = mass; }
	
	//添加力
	void AddForce(Vector2D force) { velocity += force * DELTA_TIME/mass; }
	
	//添加冲量
	void AddPulse(Vector2D pulse) { velocity += pulse/mass; }

	//是否可移动
	void SetMoveable(bool moveable) { this->bMoveable = moveable; }
	
	//是否启用重力
	void SetGravityEnabled(bool enabled) { this->bGravityEnabled = enabled; }
	
	//是否可旋转
	void SetRotatable(bool rotatable) { this->bRotatable = rotatable; }
};