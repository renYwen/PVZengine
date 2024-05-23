#include "UserInterface.h"


void UserInterface::Update()
{
	for (auto& widget : widgets)
	{
		if (widget->GetUIPattern() != UIPattern::None)widget->Update();
	}
}

void UserInterface::AddToViewport()
{
	for (auto& widget : widgets)
	{
		widget->SetUIPattern(UIPattern::VisibleAndInteractive);
	}
}

void UserInterface::HideFromViewport()
{
	for (auto& widget : widgets)
	{
		widget->SetUIPattern(UIPattern::None);
	}
}

void UserInterface::RemoveFromViewport()
{
	mainWorld.GameUIs_to_delete.insert(this);
}