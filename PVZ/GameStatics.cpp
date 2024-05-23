#include "GameStatics.h"


GameInstance* GameStatics::GetGameInstance()
{
    return mainWorld.gameInstance;
}

Controller* GameStatics::GetController()
{
    return mainWorld.mainController;
}
