#include"Animator.h"
#include"Core/World.h"
#include"Tools/ResourceManager.h"
#include"SpriteRenderer.h"


void Animation::Tick()
{
	index = (index + 1) % num;
	if (notifications.find(index) != notifications.end())notifications[index].Execute();
}

void Animation::Load(std::string name, Vector2D delta)
{
	AnimationResource aniRes = mainWorld.resourcePool->FetchAnimation(name);
	num = aniRes.num;
	images = aniRes.images;
	offset = delta;
}



Animator::~Animator()
{
	if (rendererAttached)rendererAttached->animatorAttached = nullptr;
}

void Animator::BeginPlay()
{
	if (rendererAttached)return;

	rendererAttached = pOwner->GetComponentByClass<SpriteRenderer>();
	if(rendererAttached)rendererAttached->animatorAttached = this;
}

void Animator::Update()
{
	if (!rendererAttached||!aniNode)return;

	IMAGE* sprite = aniNode->images[aniNode->index];
	if (currentSprite != sprite)
	{
		if (currentSprite && !bIsEnabled)return;
		currentSprite = sprite;
		rendererAttached->sprite = sprite;
		rendererAttached->spriteInfo.offset = aniNode->offset;
		rendererAttached->spriteInfo.endLoc = { sprite->getwidth(), sprite->getheight() };
	
		rendererAttached->DealImage();
	}
}

void Animator::Insert(std::string name, Animation& ani)
{
	if(ani.images)animations.insert({ name,ani });
}

Animation* Animator::GetNode() const
{
	return aniNode;
}

void Animator::SetNode(std::string nodeName)
{
	if (aniNode)aniNode->clock.Stop();
	aniNode = &(animations.find(nodeName)->second);
	aniNode->clock.Continue();
}

void Animator::SetupAttachment(SpriteRenderer* renderer)
{
	rendererAttached = renderer;
	renderer->animatorAttached = this;
}

void Animator::Activate()
{
	Super::Activate();
	if (aniNode)aniNode->clock.Continue();
}

void Animator::Deactivate()
{
	Super::Deactivate();
	if (aniNode)aniNode->clock.Stop();
}


