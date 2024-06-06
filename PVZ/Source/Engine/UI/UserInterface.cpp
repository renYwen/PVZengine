#include "UserInterface.h"
#include "Core/World.h"



void UserInterface::Update()
{
	for (auto& widget : widgets)
	{
		if (widget->GetUIPattern() != UIPattern::None)widget->Update();
	}
}

void UserInterface::ShowInfoBoxs()
{
	for (auto& widget : widgets) { widget->ShowInfoBox(); }
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