#include "BattleController.h"
#include "BattleUI.h"
#include "GameplayStatics.h"



BattleController::BattleController()
{
	BattleUI* ui = GameplayStatics::CreateUI<BattleUI>();
	ui->AddToViewport();
}

void BattleController::SetupInputComponent(InputComponent* inputComponent)
{
	Super::SetupInputComponent(inputComponent);
}



void BattleController::Update()
{
	Super::Update();
}



