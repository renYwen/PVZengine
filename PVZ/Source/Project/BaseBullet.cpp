#include"BaseBullet.h"
#include"BaseZombie.h"
#include"Components/Collider.h"


BaseBullet::BaseBullet()
{
	renderer = GetComponentByClass<SpriteRenderer>();
	renderer->SetLayer(2);
	circle = ConstructComponent<CircleCollider>();
	circle->AttachTo(root);
	circle->SetRadius(14);
	circle->SetType(CollisionType::Bullet);
}

void BaseBullet::BeginPlay()
{
	Sprite::BeginPlay();
	circle->OnComponentBeginOverlap.AddDynamic(this,&BaseBullet::OnOverlap);
}

void BaseBullet::OnOverlap(Collider* overlapComp, Collider* otherComp, Object* otherActor)
{
	BaseZombie* ABaseZombie = Cast<BaseZombie>(otherActor);
	if (!ABaseZombie)return;

	ABaseZombie->GetDamage(damage);
	Destroy();
}
