#include"BattleLevel.h"
#include"BattleController.h"
#include"GameplayStatics.h"
#include"Components/SpriteRenderer.h"


#include"PeaShooter.h"
#include"SunFlower.h"
#include"NormalZombie.h"




void BattleLevel::BeginPlay()
{
	mainController = GameplayStatics::CreateObject<BattleController>();
	mainController->SetLocalPosition(Vector2D(225.f, 300.f));

	Sprite* background0 = GameplayStatics::CreateObject<Sprite>();
	background0->LoadSprite("bg0");
	background0->SetLocalPosition(Vector2D(300, 300));
	background0->GetComponentByClass<SpriteRenderer>()->SetLayer(-5);

	GameplayStatics::CreateObject<PeaShooter>(Vector2D(100, 400));
	GameplayStatics::CreateObject<NormalZombie>(Vector2D(500, 400));
	GameplayStatics::CreateObject<SunFlower>(Vector2D(100, 500));
}

void BattleLevel::Update()
{

}


