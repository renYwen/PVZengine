#include "SeedUI.h"

SeedUI::SeedUI()
{
	button = AddWidget<Button>();
	button->AttachTo(rootCanvas);
	button->SetLayoutPattern(LayoutPattern::Center);
	button->SetSize(rootCanvas->GetSize());
	button->SetLayer(-2);
}
