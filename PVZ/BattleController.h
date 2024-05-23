#pragma once
#include"Controller.h"
#include"Timer.h"


class BattleController : public Controller
{
	DEFINE_SUPER(Controller)
	class Camera* camera;
	Timer OverallTimeHandle;
	Timer ShakeTimeHandle;
	float armLength = 20;
public:
	BattleController();

	virtual void SetupInputComponent(InputComponent* inputComponent)override;

	void Update();

	void MoveRight();

	void MoveLeft();

	void Jump();

	void MoveDown();

	void ZoomIn();

	void ZoomOut();
};