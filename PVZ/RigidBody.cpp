#include "RigidBody.h"
#include "Math.h"
#include "Collider.h"





RigidBody::~RigidBody()
{
	for(auto& collider : colliders)collider->rigidAttached = nullptr;
}

void RigidBody::Update()
{
	if (!pOwner)return;

	if (bMoveable) 
	{
		if (bGravityEnabled)velocity.y += gravity * DELTA_TIME;

		for (auto& collider : colliders)
		{
			if (collider->mode != CollisionMode::Collision)continue;
			for (auto& another : collider->collisions)
			{
				if (collider->mode != CollisionMode::Collision)continue;
				RestrictVelocity(-collider->CollisionHit(another).ImpactNormal, another->rigidAttached);
			}
		}
		for (auto& collider : colliders)
		{
			if (collider->mode != CollisionMode::Collision)continue;
			for (auto& another : collider->collisions)
			{
				if (collider->mode != CollisionMode::Collision || another->rigidAttached)continue;
				RestrictVelocity(-collider->CollisionHit(another).ImpactNormal);
			}
		}
		pOwner->AddPosition(Vector2D(Math::Clamp(velocity.x, -maxSpeed, maxSpeed), Math::Clamp(velocity.y, -maxSpeed, maxSpeed)) * DELTA_TIME);
	}
	
	if (bRotatable)pOwner->AddRotation(angularVelocity * DELTA_TIME);
}

void RigidBody::RestrictVelocity(Vector2D impactNormal, RigidBody* another)
{
	Vector2D tangentVector = { impactNormal.y, -impactNormal.x };

	Vector2D normalVelocity = Vector2D::ProjectVector(velocity, impactNormal);
	Vector2D tangentVelocity = Vector2D::ProjectVector(velocity, tangentVector);

	float friction = 0.2f; // 摩擦系数

	if (!another)
	{
		if (Vector2D::DotProduct(velocity, impactNormal) < 0) 
		{
			float multiplier = (tangentVelocity.Size() - normalVelocity.Size()*friction) / tangentVelocity.Size();
			multiplier = Math::Clamp(multiplier, 0.0f, 1.0f);
			velocity = tangentVelocity * multiplier;
		}
		return;
	}

	Vector2D anotherNormalVelocity = Vector2D::ProjectVector(another->velocity, impactNormal);
	Vector2D anotherTangentVelocity = Vector2D::ProjectVector(another->velocity, tangentVector);


	/* 弹性碰撞处理逻辑 */
	if(Vector2D::DotProduct(normalVelocity-anotherNormalVelocity, impactNormal) >= 0)return;//确保有相碰的趋势

	float restitution = 0.25f; // 弹性碰撞系数

	Vector2D normalVelocity_ = normalVelocity;
	normalVelocity = ((mass - restitution * another->mass) * normalVelocity + (1 + restitution) * another->mass * anotherNormalVelocity) / (mass + another->mass);
	anotherNormalVelocity = ((another->mass - restitution * mass) * anotherNormalVelocity + (1 + restitution) * mass * normalVelocity_) / (mass + another->mass);
	
	velocity = normalVelocity + tangentVelocity;
	another->velocity = anotherNormalVelocity + anotherTangentVelocity;
}



