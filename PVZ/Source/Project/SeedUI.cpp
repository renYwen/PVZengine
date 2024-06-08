#include "SeedUI.h"
#include "BattleController.h"
#include "GameplayStatics.h"


std::string plantName[] = {"�㶹����","���տ�","ӣ��ը��","���","��������","��������","���컨","˫������"};
int plantPrice[] = {100,50,150,50,25,175,150,200};


SeedUI::SeedUI()
{
	button = AddWidget<Button>();
	button->AttachTo(rootCanvas);
	button->SetLayoutPattern(LayoutPattern::Center);
	button->SetSize(rootCanvas->GetSize());
	button->SetLayer(-2);
}

void SeedUI::Init(int num)
{
	number = num;
	button->LoadNormalPicture("card" + std::to_string(num));
	name = plantName[num - 1];
	price = plantPrice[num - 1];
	button->EnableInfoBox(true);
}

void SeedUI::Update()
{
	UserInterface::Update();

	if (BattleController* pController = Cast<BattleController>(GameplayStatics::GetController()))
	{
		if (pController->GetSunshineNum() >= price)
		{
			button->SetInfoText(name);
		}
		else
		{
			button->SetInfoText(std::string("$9û���㹻����\n$4") + name);
		}
	}
}
