#pragma once
#include"CoreMinimal.h"


class Actor;


/* 组件基类 */
class ActorComponent : public Object
{
protected:
	Actor* pOwner = nullptr;//处理控制逻辑
public:
	virtual void Update() {}

	virtual void BeginPlay() {}

	//设置绑定对象
	void SetOwner(Actor* owner);

	//销毁组件
	virtual void Destruct();
};