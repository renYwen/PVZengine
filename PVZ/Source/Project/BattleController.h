#pragma once
#include"Objects/Controller.h"
#include"Tools/Timer.h"


class BattleController : public Controller
{
	DEFINE_SUPER(Controller)

	friend class SeedUI;
	

	Timer OverallTimeHandle;

	int sunshine = 100;

	class BasePlant* seedToPlant = nullptr;
public:
	BattleController();

	virtual void SetupInputComponent(InputComponent* inputComponent)override;

	void Update();

	int GetSunshineNum() const { return sunshine; }

	void SetSunshineNum(int num) { sunshine = num; }

	void PlantSeed();
};