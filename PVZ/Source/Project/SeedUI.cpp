#include "SeedUI.h"
#include "BattleController.h"
#include "GameplayStatics.h"

#include"PeaShooter.h"
#include"SunFlower.h"


std::string plantName[] = {"豌豆射手","向日葵","樱桃炸弹","坚果","土豆地雷","寒冰射手","大嘴花","双发射手"};
int plantPrice[] = {100,50,150,50,25,175,150,200};
float coolingTime[] = {5,5,45,30,30,5,5,5};


SeedUI::SeedUI()
{
	button = AddWidget<Button>();
	button->AttachTo(rootCanvas);
	button->SetLayoutPattern(LayoutPattern::Center);
	button->SetSize(rootCanvas->GetSize());
	button->SetLayer(-2);

	black = AddWidget<Image>();
	black->AttachTo(rootCanvas);
	black->SetLayoutPattern(LayoutPattern::Center);
	black->SetSize(rootCanvas->GetSize());
	black->SetLayer(0);
	black->LoadSprite("black");
	black->SetTransparency(125);

	gray = AddWidget<Image>();
	gray->AttachTo(rootCanvas);
	gray->SetLayoutPattern(LayoutPattern::Center);
	gray->SetSize(rootCanvas->GetSize());
	gray->SetLayer(-1);
	gray->LoadSprite("gray");
	gray->SetTransparency(125);
}

void SeedUI::Init(int num)
{
	number = num;
	button->LoadNormalPicture("card" + std::to_string(number+1));
	button->EnableInfoBox(true);
	button->OnMousePressedBegin.AddDynamic(this,&SeedUI::ReadyToPlant);
}

void SeedUI::Update()
{
	UserInterface::Update();

	if (BattleController* pController = Cast<BattleController>(GameplayStatics::GetController()))
	{
		if (CoolingTimerHandle.GetDelay() < coolingTime[number])
			button->SetInfoText("$9冷却中\n$4" + plantName[number]);
		else if (pController->GetSunshineNum() < plantPrice[number])
			button->SetInfoText("$9没有足够阳光\n$4" + plantName[number]);
		else 
			button->SetInfoText(plantName[number]);


		if (pController->GetSunshineNum() < plantPrice[number] || CoolingTimerHandle.GetDelay() < coolingTime[number])
			gray->SetTransparency(125);
		else gray->SetTransparency(0);


		if (CoolingTimerHandle.GetDelay() < coolingTime[number])
		{
			black->SetStartAndEndLoc(Pair(),Pair(black->GetSize().x,
				black->GetSize().y * (1 - CoolingTimerHandle.GetDelay() / coolingTime[number])));
		}
	}
}

void SeedUI::ReadyToPlant()
{
	if (BattleController* pController = Cast<BattleController>(GameplayStatics::GetController()))
	{
		if (CoolingTimerHandle.GetDelay() < coolingTime[number] || pController->GetSunshineNum() < plantPrice[number])return;
			
		switch (number)
		{
		case 0: pController->seedToPlant = GameplayStatics::CreateObject<PeaShooter>(); break;
		case 1: pController->seedToPlant = GameplayStatics::CreateObject<SunFlower>(); break;
		}

		/*pController->sunshine -= plantPrice[number];*/
	}
}
