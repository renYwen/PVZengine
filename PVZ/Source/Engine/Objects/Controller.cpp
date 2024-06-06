#include "Controller.h"
#include "Components/Camera.h"
#include "Components/Collider.h"
#include "Tools/Math.h"



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

HitResult Controller::GetHitResultUnderCursor()
{
	Vector2D pos = inputComponent->GetMousePosition();
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


