#pragma once
#include"Components/ActorComponent.h"



/* 刚体组件 */
class RigidBody final:public ActorComponent
{
	friend class Collider;
public:
	virtual ~RigidBody();
	virtual void Update() override;

	//设置重力
	void SetGraivty(float gravity) { this->gravity = gravity; }
	
	//设置速度
	void SetVelocity(Vector2D velocity) { this->velocity = velocity; }
	
	//设置速度最大值
	void SetMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
	
	//设置角速度
	void SetAngularVelocity(float angularVelocity) { this->angularVelocity = angularVelocity; }
	
	//设置质量
	void SetMass(float mass) { this->mass = mass; }
	
	//添加力
	void AddForce(Vector2D force) { velocity += force * DELTA_TIME/mass; }
	
	//添加冲量
	void AddPulse(Vector2D pulse) { velocity += pulse/mass; }

	//是否可移动
	void SetMoveable(bool moveable) { this->bMoveable = moveable;if(!moveable)velocity = Vector2D(0, 0); }
	
	//是否启用重力
	void SetGravityEnabled(bool enabled) { this->bGravityEnabled = enabled; }
	
	//是否可旋转
	void SetRotatable(bool rotatable) { this->bRotatable = rotatable;if(!rotatable)angularVelocity = 0; }

private:
	Vector2D velocity = Vector2D(0, 0);
	float maxSpeed = 1000.0f;
	bool bMoveable = true;
	float gravity = 98.f;
	bool bGravityEnabled = true;
	float angularVelocity = 0;
	bool bRotatable = true;
	float mass = 1.0f;

	std::unordered_set<Collider*> colliders;
	void RestrictVelocity(Vector2D impactNormal,RigidBody* another = nullptr);
};