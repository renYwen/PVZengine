#include "BattleController.h"
#include "Camera.h"


BattleController::BattleController()
{
	camera = GetComponentByClass<Camera>();
	SetLocalPosition(Vector2D(0.f, 300.f));
}

void BattleController::SetupInputComponent(InputComponent* inputComponent)
{
	Super::SetupInputComponent(inputComponent);

	inputComponent->SetMapping("MoveRight", KeyCode::VK_D);
	inputComponent->BindAction("MoveRight", InputType::Holding, this, &BattleController::MoveRight);
	inputComponent->SetMapping("MoveLeft", KeyCode::VK_A);
	inputComponent->BindAction("MoveLeft", InputType::Holding, this, &BattleController::MoveLeft);
	inputComponent->SetMapping("MoveUp", KeyCode::VK_K);
	inputComponent->BindAction("MoveUp", InputType::Pressed, this, &BattleController::Jump);
	inputComponent->SetMapping("MoveDown", KeyCode::VK_S);
	inputComponent->BindAction("MoveDown", InputType::Holding, this, &BattleController::MoveDown);

	inputComponent->SetMapping("ZoomIn", KeyCode::VK_Q);
	inputComponent->BindAction("ZoomIn", InputType::Holding, this, &BattleController::ZoomIn);
	inputComponent->SetMapping("ZoomOut", KeyCode::VK_E);
	inputComponent->BindAction("ZoomOut", InputType::Holding, this, &BattleController::ZoomOut);
}



void BattleController::Update()
{
	Super::Update();
	
	/*if (OverallTimeHandle.GetDelay() > 2.f && OverallTimeHandle.GetDelay() <= 5.f && 
		GetWorldPosition().x < 600) {
		AddPosition(Vector2D(5.f, 0));
	}
	if(OverallTimeHandle.GetDelay() > 7.f && GetWorldPosition().x >= 225.f)
	{ 
	    AddPosition(Vector2D(-5.f, 0));
	}*/
}


void BattleController::MoveRight()
{
	AddPosition(Vector2D(0.5f, 0));
}

void BattleController::MoveLeft()
{
	AddPosition(Vector2D(-0.5f, 0));
}

void BattleController::Jump()
{
	AddPosition(Vector2D(0, -100.f));
}

void BattleController::MoveDown()
{
	AddPosition(Vector2D(0, 0.5f));
}

void BattleController::ZoomIn()
{
	camera->SetSpringArmLength(armLength-=0.05f);
}

void BattleController::ZoomOut()
{
	camera->SetSpringArmLength(armLength+=0.05f);
}

