#include"CoreMinimal.h"

#include <windows.h>
#pragma comment(lib,"winmm.lib")
//#include <future>

#include"ResourceManager.h"
#include"CollisionManager.h"
#include"GameStatics.h"
#include"Timer.h"

#include"BattleLevel.h"
#include"BattleController.h"


//std::future<void> m_updateFuture;
//std::future<void> m_renderFuture;
//std::future<void> m_inputFuture;

class Engine
{
public:
	static void Init()
	{
		initgraph(WIN_WIDTH, WIN_HEIGHT,1);

		setlinestyle(PS_SOLID | PS_JOIN_BEVEL);
		setfillcolor(LIGHTBLUE);
		setlinecolor(LIGHTBLUE);
		//系统Debug绘制参数

		setbkmode(TRANSPARENT);
		settextstyle(25, 10, "Arial");
		settextcolor(WHITE);
		//系统文字参数

		BeginBatchDraw();

		mainWorld.resourcePool = new ResourceManager;
		mainWorld.resourcePool->Initialize();
		//初始化资源管理器

		mainWorld.collisionManager = new CollisionManager;
		mainWorld.collisionManager->Initialize();
		//初始化碰撞管理器

		mainWorld.currentLevel = new BattleLevel;
		mainWorld.gameInstance = new GameInstance;
		mainWorld.mainController = GameStatics::CreateObject<BattleController>();
		mainWorld.FPSClock = new Timer;
		//初始化游戏世界
	}

	static void Tick()//帧更新
	{
		/*m_updateFuture = std::async(std::launch::async, &World::Update, &mainWorld);
		m_renderFuture = std::async(std::launch::async, &World::Render, &mainWorld);
		m_inputFuture = std::async(std::launch::async, &World::Input, &mainWorld);
		m_updateFuture.wait();
		m_renderFuture.wait();
		m_inputFuture.wait();*/
		mainWorld.Update();
		mainWorld.Render();
	}

	static void Tick_()//高频更新
	{
	    mainWorld.Input();
		mainWorld.Update_();
	}


	static void Exit()
	{
		; 
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


void main()
{
	Engine::Init();
	
	timeSetEvent(UINT(DELTA_TIME * 1000), 0, timecallback, 0, TIME_CALLBACK_FUNCTION|TIME_PERIODIC);
	timeSetEvent(1, 0, timecallback_,0, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
	
	Sleep(INFINITE);
}


