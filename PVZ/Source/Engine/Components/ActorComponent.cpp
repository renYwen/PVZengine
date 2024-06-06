#include "ActorComponent.h"
#include "Objects/Actor.h"


void ActorComponent::SetOwner(Actor* owner)
{
	pOwner = owner;
}

void ActorComponent::Destruct()
{
	pOwner->UnregisterComponent(this);
	delete this;
}
