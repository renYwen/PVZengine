#pragma once
#include"ActorComponent.h"
#include"Tools/Timer.h"
#include"Tools/Delegate.h"
#include<unordered_map>



/* 动画委托 */
DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(AnimationDelegate)


class IMAGE;

/* 动画源 */
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
	Animation() { clock.Bind(0, this, &Animation::Tick, true); clock.Stop();}

	void Load(std::string name, Vector2D delta = {0,0});

	//设置动画帧间隔时间
	void SetInterval(double interval) { clock.SetDelay(interval); }

	//设置动画帧下标
	void SetIndex(int i) { index = i; }

	//在指定帧处添加动画通知
	void AddNotification(int index, AnimationDelegate& event) { notifications.insert({ index,event }); }
};


class SpriteRenderer;

/* 动画播放器 */
class Animator final: public ActorComponent
{
	DEFINE_SUPER(ActorComponent)

    friend SpriteRenderer;
public:
	virtual ~Animator();
	virtual void BeginPlay() override;
	virtual void Update() override;

	virtual void Activate()override;
	virtual void Deactivate()override;

	//插入动画节点
	void Insert(std::string name, Animation& ani);

	//获取当前动画节点
	Animation* GetNode()const;

	//设置动画节点
	void SetNode(std::string nodeName);

	//设置附着渲染器
	void SetupAttachment(SpriteRenderer*renderer);
private:
	std::unordered_map<std::string, Animation&> animations;

	Animation* aniNode = nullptr;//当前播放的动画

	SpriteRenderer* rendererAttached = nullptr;//附着的渲染器

	IMAGE* currentSprite = nullptr;//当前播放的图像
};