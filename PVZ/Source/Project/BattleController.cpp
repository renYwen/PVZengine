#include "BattleController.h"
#include "BattleUI.h"
#include "GameplayStatics.h"
#include "BasePlant.h"
//#include "Sun.h"


BattleController::BattleController()
{
	BattleUI* ui = GameplayStatics::CreateUI<BattleUI>();
	ui->AddToViewport();
}

void BattleController::SetupInputComponent(InputComponent* inputComponent)
{
	Super::SetupInputComponent(inputComponent);

	inputComponent->SetMapping("Plant",KeyCode::VK_LButton);
	inputComponent->BindAction("Plant",InputType::Pressed,this,&BattleController::PlantSeed);
}



void BattleController::Update()
{
	Super::Update();
	
	if (seedToPlant)
	{
		seedToPlant->SetLocalPosition(GetCursorPosition());
		
	}


}

void BattleController::PlantSeed()
{
	if (seedToPlant)
	{
		seedToPlant->Activate();
		sunshine -= seedToPlant->GetCost();
		seedToPlant = nullptr;
	}
}
