#pragma once
#include"Components/InputComponent.h"
#include"Actor.h"




//玩家控制器类
class Controller :public Actor
{
	DEFINE_SUPER(Actor)

	InputComponent* inputComponent;
	class Camera* camera;

protected:
	virtual void SetupInputComponent(InputComponent* inputComponent) { ; }
public:
	Controller();

	virtual void BeginPlay() override;

	void PeekInfo() { inputComponent->Update(); }

	Vector2D GetCursorPosition() const { return InputComponent::GetMousePosition(); }

	bool IsMouseClicked() const { return InputComponent::IsMouseButtonPressed(); }

	struct HitResult GetHitResultUnderCursor();//该物体必须拥有碰撞体
};