#include "BattleLevel.h"
#include"GameStatics.h"
#include"SpriteRenderer.h"
#include"BattleController.h"

#include"PeaShooter.h"
#include"SunFlower.h"
#include"NormalZombie.h"



BattleLevel::BattleLevel()
{
	background0 = GameStatics::CreateObject<Sprite>();
	background0->LoadSprite("bg0");
	background0->SetLocalPosition(Vector2D(300, 300));

	GameStatics::CreateObject<PeaShooter>(Vector2D(100, 400));
	GameStatics::CreateObject<NormalZombie>(Vector2D(500,400));
	GameStatics::CreateObject<SunFlower>(Vector2D(100, 500));
}

void BattleLevel::Update()
{

}


