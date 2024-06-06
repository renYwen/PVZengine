#include "GameplayStatics.h"
#include "Objects/Controller.h"
#include "LevelManager.h"

GameInstance* GameplayStatics::GetGameInstance()
{
    if(!mainWorld.gameInstance)mainWorld.gameInstance = new GameInstance;
    return mainWorld.gameInstance;
}

Controller* GameplayStatics::GetController()
{
    Controller* pController = mainWorld.currentLevel->mainController;
    if (!pController)pController = CreateObject<Controller>();
    return pController;
}

void GameplayStatics::OpenLevel(std::string levelName)
{
    mainWorld.levelManager->SetDefaultLevel(levelName);
}
