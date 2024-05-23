#include "RigidBody.h"
#include "Math.h"
#include "Collider.h"




void RigidBody::RestrictVelocity(Vector2D impactNormal)
{
	if(Vector2D::DotProduct(velocity, impactNormal) < 0)
	velocity = Vector2D::ProjectVector(velocity, {impactNormal.y, -impactNormal.x});
}

void RigidBody::Update()
{
	if (pOwner) {
		if (bMoveable) {
			if (bGravityEnabled)velocity.y += gravity * DELTA_TIME;

			for (auto&obj:pOwner->components)
			{
				if (Collider* collider = Cast<Collider>(obj)) 
				{
					if (collider->mode != CollisionMode::Collision)return;
					for (auto& collider2 : collider->collisions)
					{
						if(collider2->mode != CollisionMode::Collision)continue;
						RestrictVelocity(-collider->CollisionHit(collider2).ImpactNormal);
					}
				}
			}

			pOwner->AddPosition(Vector2D(Math::Clamp(velocity.x, -maxSpeed, maxSpeed),
				Math::Clamp(velocity.y, -maxSpeed, maxSpeed))* DELTA_TIME);
		}
		if (bRotatable)pOwner->AddRotation(angularVelocity*DELTA_TIME);
	}
}



