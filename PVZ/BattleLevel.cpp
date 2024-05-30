#include "BattleLevel.h"
#include"GameStatics.h"
#include"SpriteRenderer.h"
#include"BattleController.h"

#include"PeaShooter.h"
#include"NormalZombie.h"
#include"Math.h"


BattleLevel::BattleLevel()
{
	background0 = GameStatics::CreateObject<Sprite>();
	background0->LoadSprite("bg0");
	background0->SetLocalPosition(Vector2D(300, 300));

	/*for (int i = 0;i<200;i++)
	{
		GameStatics::CreateObject<PeaShooter>(Vector2D((i/20)*125-200, (i%10)*75-100));
	}*/
	GameStatics::CreateObject<PeaShooter>(Vector2D(100, 400));
	GameStatics::CreateObject<NormalZombie>(Vector2D(500,400));

}

void BattleLevel::Update()
{

}


