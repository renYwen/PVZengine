#pragma once
#include"CoreMinimal.h"
#include"Tools/Timer.h"
#include"Tools/Delegate.h"
#include"easyx.h"
#include<unordered_map>



//动画委托
DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(AnimationDelegate)


//动画源
class Animation final
{
    friend class Animator;

	int num = 0;//动画帧数
	Vector2D offset = {0,0};//偏移量
	IMAGE**images = nullptr;//动画帧数组
	int index = 0;//当前帧索引

	Timer clock;//计时器

	std::unordered_map<int, AnimationDelegate>notifications;//自定义动画通知

	void Tick();

public:
	Animation() { clock.Bind(0, this, &Animation::Tick, true); clock.Stop(); }

	void Load(std::string name, Vector2D delta = {0,0});

	//设置动画帧间隔时间
	void SetInterval(double interval) { clock.SetDelay(interval); }

	//设置下标
	void SetIndex(int i) { index = i; }

	//在指定帧处添加动画通知
	void AddNotification(int index, AnimationDelegate& event) { notifications.insert({ index,event }); }
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

	//设置动画节点
	void SetNode(std::string nodeName);

	//设置动画是否播放
	void SetCalled(bool called);
};