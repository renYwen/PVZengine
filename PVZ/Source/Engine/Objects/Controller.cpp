#include "Controller.h"
#include "Components/Camera.h"
#include "Tools/Math.h"
#include "Core/World.h"



Controller::Controller()
{
	camera = ConstructComponent<Camera>();
	camera->AttachTo(root);
	camera->SetMainCamera();

	inputComponent = ConstructComponent<InputComponent>();
}

void Controller::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent(inputComponent);
}

void Controller::PeekInfo()
{
	inputComponent->Update();
}

Vector2D Controller::GetCursorPosition() const
{
	return InputComponent::GetMousePosition() + mainWorld.mainCamera->GetWorldPosition() - Vector2D(WIN_WIDTH,WIN_HEIGHT)/2;
}

bool Controller::IsMouseClicked() const
{
	return InputComponent::IsMouseButtonPressed();
}

HitResult Controller::GetHitResultUnderCursor()
{
	Vector2D pos = GetCursorPosition();
	int x = Math::Clamp(int(pos.x) / 100, 0, 7);
	int y = Math::Clamp(int(pos.y) / 100, 0, 5);

	if (!mainWorld.ColliderZones[x][y].empty())
	{
		for (auto it = mainWorld.ColliderZones[x][y].rbegin(); it != mainWorld.ColliderZones[x][y].rend(); ++it)
		{
			if ((*it)->IsMouseOver())return HitResult(pos, {0,0}, (*it)->pOwner, *it);
		}
	}
	return HitResult();
}

void Controller::EnableInput(bool enable)
{
	InputComponent::EnableInput(enable);
}


