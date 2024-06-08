#include"CoreMinimal.h"
#include"World.h"

#include"Tools/ResourceManager.h"
#include"Tools/CollisionManager.h"
#include"Tools/LevelManager.h"

#include"GameplayStatics.h"
#include"Tools/Timer.h"

#include <easyx.h>
#include <windows.h>
#pragma comment(lib,"winmm.lib")




class Engine
{
public:
	static void Init()
	{
		initgraph(WIN_WIDTH, WIN_HEIGHT,1);

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL);
		setfillcolor(LIGHTBLUE);
		setlinecolor(LIGHTBLUE);
		//ϵͳDebug���Ʋ���

		setbkmode(TRANSPARENT);
		settextstyle(25, 10, "Arial");
		settextcolor(WHITE);
		//ϵͳ���ֲ���

		BeginBatchDraw();

		mainWorld.resourcePool = new ResourceManager;
		mainWorld.resourcePool->Initialize();
		//��ʼ����Դ������

		mainWorld.collisionManager = new CollisionManager;
		mainWorld.collisionManager->Initialize();
		//��ʼ����ײ������

		mainWorld.levelManager = new LevelManager;
		mainWorld.levelManager->Initialize();
		mainWorld.currentLevel->BeginPlay();
		mainWorld.FPSClock = new Timer;
		//��ʼ����Ϸ����
	}

	static void Tick()//֡����
	{
		mainWorld.Update();
		mainWorld.Render();
	}

	static void Tick_()//��Ƶ����
	{
	    mainWorld.Input();
		mainWorld.Update_();
	}


	static void Exit()
	{
		delete mainWorld.gameInstance; 
	}
};



void CALLBACK timecallback(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
	Engine::Tick();
}

void CALLBACK timecallback_(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
	Engine::Tick_();
}


int main()
{
	Engine::Init();
	
	timeSetEvent(UINT(DELTA_TIME * 1000), 0, timecallback, 0, TIME_CALLBACK_FUNCTION|TIME_PERIODIC);
	timeSetEvent(1, 0, timecallback_,0, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
	
	Sleep(INFINITE);
	return 0;
}


