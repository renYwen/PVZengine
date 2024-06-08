#pragma once
#include"Objects/Controller.h"
#include"Tools/Timer.h"


class BattleController : public Controller
{
	DEFINE_SUPER(Controller)
	
	Timer OverallTimeHandle;
public:
	BattleController();

	virtual void SetupInputComponent(InputComponent* inputComponent)override;

	void Update();
};