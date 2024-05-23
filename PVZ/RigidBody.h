#pragma once
#include"CoreMinimal.h"



//�������
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
	
	//�����
	void AddForce(Vector2D force) { velocity += force * DELTA_TIME/mass; }
	
	//��ӳ���
	void AddPulse(Vector2D pulse) { velocity += pulse/mass; }

	//�Ƿ���ƶ�
	void SetMoveable(bool moveable) { this->bMoveable = moveable; }
	
	//�Ƿ���������
	void SetGravityEnabled(bool enabled) { this->bGravityEnabled = enabled; }
	
	//�Ƿ����ת
	void SetRotatable(bool rotatable) { this->bRotatable = rotatable; }
};