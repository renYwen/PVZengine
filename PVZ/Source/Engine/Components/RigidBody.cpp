#include "RigidBody.h"
#include "Collider.h"
#include "Tools/Math.h"
#include "Objects/Actor.h"





RigidBody::~RigidBody()
{
	for(auto& collider : colliders)collider->rigidAttached = nullptr;
}

void RigidBody::Update()
{
	if (!pOwner||!bIsEnabled)return;

	if (bMoveable) 
	{
		if (bGravityEnabled)velocity.y += gravity * DELTA_TIME;

		for (auto& collider : colliders)
		{
			if (collider->mode != CollisionMode::Collision)continue;
			for (auto& another : collider->collisions)
			{
				if (collider->mode != CollisionMode::Collision)continue;
				RestrictVelocity(-collider->CollisionHit(another).ImpactNormal, 
					PhysicsMaterial::Combine(collider->material,another->material), another->rigidAttached);
			}
		}
		for (auto& collider : colliders)
		{
			if (collider->mode != CollisionMode::Collision)continue;
			for (auto& another : collider->collisions)
			{
				if (collider->mode != CollisionMode::Collision || another->rigidAttached)continue;
				RestrictVelocity(-collider->CollisionHit(another).ImpactNormal, 
					PhysicsMaterial::Combine(collider->material, another->material));
			}
		}
		pOwner->AddPosition(Vector2D(Math::Clamp(velocity.x, -maxSpeed, maxSpeed), Math::Clamp(velocity.y, -maxSpeed, maxSpeed)) * DELTA_TIME);
		if (linearDrag) {
			float buffer = velocity.x - velocity.x * linearDrag * DELTA_TIME / mass;
			velocity.x = ((*(int*)&velocity.x) ^ (*(int*)&buffer)) < 0 ? 0 : buffer;
			buffer = velocity.y - velocity.y * linearDrag * DELTA_TIME / mass;
			velocity.y = ((*(int*)&velocity.y) ^ (*(int*)&buffer)) < 0 ? 0 : buffer;
		}
	}

	if (bRotatable)
	{
		pOwner->AddRotation(angularVelocity * DELTA_TIME); 
		if (angularDrag) {
			float buffer = angularVelocity - angularVelocity * angularDrag * DELTA_TIME / mass;
			angularVelocity = ((*(int*)&angularVelocity) ^ (*(int*)&buffer)) < 0 ? 0 : buffer;
		}
	}
}

void RigidBody::RestrictVelocity(Vector2D impactNormal,const PhysicsMaterial& material,RigidBody* another)
{
	Vector2D tangentVector = { impactNormal.y, -impactNormal.x };

	Vector2D normalVelocity = Vector2D::ProjectVector(velocity, impactNormal);
	Vector2D tangentVelocity = Vector2D::ProjectVector(velocity, tangentVector);

	float friction = material.friction;
	float bounciness = material.bounciness;

	if (!another)
	{
		if (Vector2D::DotProduct(velocity, impactNormal) < 0) 
		{
			float multiplier = (tangentVelocity.Size() - normalVelocity.Size()*friction) / tangentVelocity.Size();
			multiplier = Math::Clamp(multiplier, 0.0f, 1.0f);
			velocity = tangentVelocity * multiplier - bounciness * normalVelocity;
		}
		return;
	}

	Vector2D anotherNormalVelocity = Vector2D::ProjectVector(another->velocity, impactNormal);
	Vector2D anotherTangentVelocity = Vector2D::ProjectVector(another->velocity, tangentVector);


	/* 弹性碰撞处理逻辑 */
	if(Vector2D::DotProduct(normalVelocity - anotherNormalVelocity, impactNormal) >= 0)return;//确保有相碰的趋势

	
	Vector2D normalVelocity_ = normalVelocity;
	normalVelocity = ((mass - bounciness * another->mass) * normalVelocity + (1 + bounciness) * another->mass * anotherNormalVelocity) / (mass + another->mass);
	anotherNormalVelocity = ((another->mass - bounciness * mass) * anotherNormalVelocity + (1 + bounciness) * mass * normalVelocity_) / (mass + another->mass);
	
	velocity = normalVelocity + tangentVelocity;
	another->velocity = anotherNormalVelocity + anotherTangentVelocity;
}



