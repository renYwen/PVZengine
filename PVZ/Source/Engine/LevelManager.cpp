#include "LevelManager.h"
#include "BattleLevel.h"



void LevelManager::Initialize()
{
	AddLevel<BattleLevel>("DayLawn");
	SetDefaultLevel("DayLawn");
}

void LevelManager::SetDefaultLevel(std::string levelName)
{
	level_to_delete = mainWorld.currentLevel;
	if (levelMap.find(levelName) == levelMap.end())return;
	mainWorld.currentLevel = levelMap[levelName];
}

void LevelManager::RefreshLevel()
{
	if (level_to_delete)
	{
		mainWorld.WipeData();
		level_to_delete = nullptr;
		mainWorld.currentLevel->BeginPlay();
	}
}
