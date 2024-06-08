#include"World.h"
#include"GameplayStatics.h"
#include"Tools/LevelManager.h"
#include"Tools/Timer.h"
#include"Tools/VisualInterface.h"
#include"Components/Camera.h"
#include"Components/Collider.h"
#include"Objects/Controller.h"
#include"UI/UserInterface.h"



int Object::tag = 0;

extern World mainWorld{};


bool LayerSort::operator()(const LayerInterface* a, const LayerInterface* b) const
{
	if (a->GetLayer() == b->GetLayer()) return a < b;
	else return a->GetLayer() < b->GetLayer();
}

bool ColliderSort::operator()(const Collider* a, const Collider* b)const
{
	if (a->GetLayer() == b->GetLayer()) return a < b;
	else return a->GetLayer() < b->GetLayer();
}




void World::Update()
{
	ProcessColliders();

	currentLevel->Update();

	for (auto& obj : GameActors)obj->Update();
	for (auto& obj : GameActors_to_add)
	{
		GameActors.insert(obj);
		obj->BeginPlay();
	}
	GameActors_to_add.clear();
	for (auto& obj : GameActors_to_delete)
	{
		GameActors.erase(obj);
		delete obj;
	}
	GameActors_to_delete.clear();
	for (auto& obj : GameUIs)obj->Update();
	for (auto& obj : GameUIs_to_delete)
	{
		GameUIs.erase(obj);
		delete obj;
	}
	GameUIs_to_delete.clear();
	for (auto& obj : GameTimers)
	{
		obj->Execute();
	}

	/* 检查关卡更新 */
	levelManager->RefreshLevel();
}


void World::ProcessColliders()
{
	for (auto& arr_i : ColliderZones)for (auto& arr_j : arr_i) if (!arr_j.empty())
		for (auto& me : arr_j)for (auto& he : arr_j) if (he != me) me->Insert(he);
	//碰撞插入信息更新

	for (auto& it : GameColliders)it->Erase();
	//碰撞删除信息更新

	for (auto& it : GameColliders_to_clear)it->Clear();
	GameColliders_to_clear.clear();
	//碰撞体移除更新
}


void World::Render()
{
	cleardevice();

	for (auto& obj : GameRenderers) obj->Render();
	for (auto& obj : GameUIs)obj->ShowInfoBoxs();
#ifdef _DEBUG
	Debug();
#endif

	FlushBatchDraw();
}

void World::Input()
{
	GameplayStatics::GetController()->PeekInfo();
}

void World::Update_()
{
	mainCamera->Calculate();
}

void World::Debug()
{
	for (auto& obj : GameColliders)
		obj->DrawDebugLine();
	for (auto& obj : GameActors)
		obj->DrawDebugPosition();
	for (auto& obj : GameUIs)
		obj->DrawDebugRect();

	static int FPS = 0;
	static int number = 0;
	number++;

	settextstyle(25, 10, "Arial");
	settextcolor(RGB(255,200,15));
	outtextxy(0, 0, (std::string("FPS: ") + std::to_string(FPS)).c_str());
	if (FPSClock->GetDelay() >= 1.0)
	{
		FPS = number;
		FPSClock->Reset();
		number = 0;
	}
}

void World::WipeData()
{
	for (auto& obj : GameActors)delete obj;
	for (auto& obj : GameUIs)delete obj;

	GameActors.clear();
	GameActors_to_add.clear();
	GameActors_to_delete.clear();
	GameUIs.clear();
	GameUIs_to_delete.clear();
	GameColliders.clear();
	GameColliders_to_clear.clear();
	GameTimers.clear();
	GameRenderers.clear();
	for (auto& arr_i : ColliderZones)for (auto& arr_j : arr_i)arr_j.clear();
}