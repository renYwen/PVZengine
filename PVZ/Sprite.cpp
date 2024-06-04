#include "Sprite.h"
#include "Math.h"


void Sprite::Recover()
{
	blinkFlag = false;
}

Sprite::Sprite()
{
	renderer = ConstructComponent<SpriteRenderer>();
	SetRootComponent(renderer);
}

void Sprite::Update()
{
	Super::Update();
	if (isBlinking)
	{
		if (!blinkFlag) 
		{
			if (transistionLevel > 0)transistionLevel -= transistionSpeed;
			if (transistionLevel <= 0)isBlinking = false;
		}
		renderer->RemoveFilter();
		if (isBlinking)renderer->AddFilter({ blinkFilter.color, int(transistionLevel),1 });
	}
}

void Sprite::LoadSprite(std::string name)
{
	renderer->LoadSprite(name);
}

void Sprite::Blink(float duration, COLORREF color, int level)
{
	if (!isBlinking) {
		duration = Math::Clamp(duration, 0.1f, 1.f);
		blinkFlag = true;isBlinking = true;
		blinkFilter = { color, level,1 };
		transistionLevel = float(level);
		transistionSpeed = 2 * level * DELTA_TIME /duration;
		recoverTimerHandle.Bind(duration/2, this, &Sprite::Recover);
	}
}






