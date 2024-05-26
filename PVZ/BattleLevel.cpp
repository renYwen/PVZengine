#include "BattleLevel.h"
#include"GameStatics.h"
#include"SpriteRenderer.h"
#include"BattleController.h"

#include"Sun.h"
#include"Platform.h"
#include"Math.h"


BattleLevel::BattleLevel()
{
	background0 = GameStatics::CreateObject<Sprite>();
	background0->LoadSprite("bg0");
	background0->SetLocalPosition(Vector2D(300, 300));

	for (int i = 0; i < 300; i++) 
	{
		GameStatics::CreateObject<Sun>(Vector2D(Math::RandReal(-200,700), Math::RandReal(-10000,0)));
	}
	GameStatics::CreateObject<Sun>(Vector2D(-108,300));

	GameStatics::CreateObject<Platform>(Vector2D(200, 500));
	GameStatics::CreateObject<Platform>(Vector2D(-600, -400))->SetSize(Vector2D(50, 1800));
	GameStatics::CreateObject<Platform>(Vector2D(1000, -400))->SetSize(Vector2D(50, 1800));
}

void BattleLevel::Update()
{

}


