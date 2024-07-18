#include "BattleUI.h"
#include "SeedUI.h"
#include "GameplayStatics.h"
#include "BattleController.h"


BattleUI::BattleUI()
{
	SeedBank = AddWidget<Image>();
	SeedBank->AttachTo(rootCanvas);
	SeedBank->SetLayoutPattern(LayoutPattern::MiddleTop);
	SeedBank->SetRelativePosition(Vector2D(-130, 45));
	SeedBank->SetSize(Vector2D(530, 91));
	SeedBank->LoadSprite("seedbank");
	SeedBank->SetLayer(-3);

	Panel = AddWidget<HorizontalPanel>();
	Panel->AttachTo(SeedBank);
	Panel->SetLayoutPattern(LayoutPattern::Center);
	Panel->SetRelativePosition(Vector2D(33, 0));
	Panel->SetUnitSize(Vector2D(54,77));
	Panel->SetSpacing(2);
	Panel->SetLayer(-3);

	SunShine = AddWidget<Text>();
	SunShine->AttachTo(SeedBank);
	SunShine->SetRelativePosition(Vector2D(38, 77));
	SunShine->SetLayer(-2);
	
	for (int i = 0; i < 8; i++)
	{
		SeedUI* ui = GameplayStatics::CreateUI<SeedUI>();
		ui->Init(i);
		Panel->AddMember(ui);
	}
}


void BattleUI::Update()
{
	UserInterface::Update();

	if (BattleController* pController = Cast<BattleController>(GameplayStatics::GetController()))
	{
		SunShine->SetText(std::to_string(pController->GetSunshineNum()), 4);
	}

}
