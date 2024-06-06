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

void Animator::BeginPlay()
{
	rendererAttached = pOwner->GetComponentByClass<SpriteRenderer>();
}

void Animator::Update()
{
	if (!rendererAttached||!aniNode)return;

	static IMAGE* currentSprite = nullptr;
	IMAGE* sprite = aniNode->images[aniNode->index];
	if (currentSprite != sprite)
	{
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

void Animator::SetNode(std::string nodeName)
{
	if (aniNode)aniNode->clock.Stop();
	aniNode = &(animations.find(nodeName)->second);
	aniNode->clock.Continue();
}

void Animator::SetCalled(bool called)
{
	if(aniNode)called?aniNode->clock.Continue():aniNode->clock.Stop();
}
