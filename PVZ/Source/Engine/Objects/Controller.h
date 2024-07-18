#pragma once
#include"Components/InputComponent.h"
#include"Actor.h"
#include"Components/Collider.h"


class Camera;



//玩家控制器类
class Controller :public Actor
{
	DEFINE_SUPER(Actor)

	InputComponent* inputComponent;
	Camera* camera;

protected:
	virtual void SetupInputComponent(InputComponent* inputComponent) {}
public:
	Controller();

	virtual void BeginPlay() override;

	void PeekInfo();

	//获取鼠标世界坐标系位置
	Vector2D GetCursorPosition() const;

	//获取鼠标是否按下
	bool IsMouseClicked() const;

	//获取世界坐标系下鼠标所处位置最顶层的物体信息（该物体必须拥有碰撞体）
	HitResult GetHitResultUnderCursor();

	//激活输入输出
	void EnableInput(bool enable);
};