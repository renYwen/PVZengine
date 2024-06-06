#include"BaseZombie.h"
#include"Components/Collider.h"
#include"BasePlant.h"


BaseZombie::BaseZombie()
{
	renderer = GetComponentByClass<SpriteRenderer>();
	renderer->SetLayer(1);
	box = ConstructComponent<BoxCollider>();
	box->AttachTo(root);
	box->SetSize({ 40,100 });
	box->SetType(CollisionType::Zombie);

	ani = ConstructComponent<Animator>();


	die.Load("zombiedie",Vector2D(-20, -12));
	die.SetInterval(0.12f);

	ani->Insert("die", die);

	dieEvent.Bind([this]() {this->Destroy(); });
	die.AddNotification(9, dieEvent);
}

void BaseZombie::BeginPlay()
{
	Sprite::BeginPlay();
	box->OnComponentBeginOverlap.AddDynamic(this,&BaseZombie::OnOverlap);
	box->OnComponentEndOverlap.AddDynamic(this,&BaseZombie::EndOverlap);
}

void BaseZombie::Update()
{
	Sprite::Update();

	if(blood > 0 && state == ZombieState::Walking)AddPosition({-speed,0});
}

void BaseZombie::GetDamage(float damage)
{
	blood -= damage;
	Blink(0.2f,WHITE);

	if (blood <= 0)
	{
		ani->SetNode("die");
	}
}


void BaseZombie::OnOverlap(Collider* overlapComp, Collider* otherComp, Actor* otherActor)
{
	if (otherComp->GetType() != CollisionType::Plant)return;

	overlapPlants.insert(otherActor);

	if (state == ZombieState::Walking)
	{
		state = ZombieState::Standing;
		ani->SetNode("eat");
		eatingPlant = Cast<BasePlant>(otherActor);
	}

}

void BaseZombie::EndOverlap(Collider* overlapComp, Collider* otherComp, Actor* otherActor)
{
	if (otherComp->GetType() != CollisionType::Plant)return;

	overlapPlants.erase(otherActor);
	
	if (overlapPlants.empty()) 
	{ 
		state = ZombieState::Walking; 
		ani->SetNode("walk"); 
		eatingPlant = nullptr;
	}
	else
	{
		eatingPlant = Cast<BasePlant>(*overlapPlants.begin());
	}
}
