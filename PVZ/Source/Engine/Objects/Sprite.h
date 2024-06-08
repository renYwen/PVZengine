#pragma once
#include"Components/SpriteRenderer.h"
#include"Tools/Timer.h"
#include"Actor.h"




//精灵类（即支持2D渲染的游戏对象）
class Sprite :public Actor
{
	DEFINE_SUPER(Actor)

public:
	Sprite();
	virtual void Update();
	void LoadSprite(std::string name);
	void Blink(float duration = 0.2f, COLORREF color = BLACK, int level = 60);

private:
	SpriteRenderer* renderer;

	bool isBlinking = false;
	bool blinkFlag = false;
	float transistionLevel = 0;
	float transistionSpeed = 0;
	FilterInfo blinkFilter;
	Timer recoverTimerHandle;
};