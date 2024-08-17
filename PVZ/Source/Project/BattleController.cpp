#include "BattleController.h"
#include "BattleUI.h"
#include "GameplayStatics.h"
#include "BasePlant.h"
#include "Sun.h"
#include "Tools/Math.h"



BattleController::BattleController()
{
	BattleUI* ui = GameplayStatics::CreateUI<BattleUI>();
	ui->AddToViewport();

	SunshineTimerHandle.Bind(12,this,&BattleController::ProduceSunshine,true,7.5);
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

void BattleController::ProduceSunshine()
{
	Sun* sunshine = GameplayStatics::CreateObject<Sun>(Vector2D(Math::RandInt(100,700), 0));
	if (sunshine)sunshine->Fall(Math::RandInt(250, 550));
}
