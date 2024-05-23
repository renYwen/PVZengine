#pragma once
#include"CoreMinimal.h"
#include"easyx.h"
#include"Timer.h"
#include<unordered_map>


//动画源
class Animation
{
    friend class Animator;

	int num = 0;//动画帧数
	Vector2D offset = {0,0};//偏移量
	IMAGE**images = nullptr;//动画帧数组
	int index = 0;//当前帧索引

	Timer clock;//计时器

public:
	Animation() { clock.Bind(0, [this](){index = (index + 1) % num; }, true); }

	void Load(std::string name, Vector2D delta = {0,0});

	void SetInterval(double interval) { clock.SetDelay(interval); }

	void SetIndex(int i) { index = i; }
};


//动画播放器
class Animator final: public Component
{
	std::unordered_map<std::string, Animation&> animations;

	Animation* aniNode = nullptr;//当前播放的动画

	class SpriteRenderer* rendererAttached = nullptr;//附着的渲染器

public:
	virtual void BeginPlay() override;
	virtual void Update() override;

	void Insert(std::string name, Animation& ani);

	Animation* GetNode()const {return aniNode;}

	void SetNode(std::string nodeName);

	void SetCalled(bool called);
};