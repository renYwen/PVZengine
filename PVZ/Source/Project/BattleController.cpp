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

	/*inputComponent->SetMapping("scroll", KeyCode::VK_RButton);
	inputComponent->BindAction("scroll", InputType::Holding, []() {std::cout << "ok"; });*/
}



void BattleController::Update()
{
	Super::Update();
}



