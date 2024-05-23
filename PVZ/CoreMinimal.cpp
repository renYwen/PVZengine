#include"CoreMinimal.h"
#include"Timer.h"
#include"VisualInterface.h"
#include"Camera.h"
#include"Controller.h"
#include"Collider.h"
#include<stack>
#include "UserInterface.h"



int64 Base::tag = 0;

extern World mainWorld{};



void Component::Destruct()
{
	pOwner->UnregisterComponent(this);
	delete this;
}



void SceneComponent::process_Destruct()
{
	if(!children.empty())
		for (auto& child : children)child->process_Destruct();
	Component::Destruct();
}

void SceneComponent::AttachTo(SceneComponent* par)
{
	if (par) {
		par->children.insert(this); 
		parent = par;
		SetOwner(par->pOwner);
	}
}


void SceneComponent::DetachFrom(SceneComponent* par)
{
	if (par) {
		par->children.erase(this);
		parent = nullptr;
	}
}

void SceneComponent::Destruct()
{
	if(parent)parent->children.erase(this);

	process_Destruct();
}



Vector2D SceneComponent::GetWorldPosition() const
{
	if(parent)
		return parent->GetWorldPosition() + GetLocalPosition();
	else {
		if (pOwner)return pOwner->GetWorldPosition();
		else return GetLocalPosition();
	}
}

float SceneComponent::GetWorldRotation() const
{
	if (parent)
		return parent->GetWorldRotation() + GetLocalRotation();
	else {
		if (pOwner)return pOwner->GetWorldRotation();
		else return GetLocalRotation();
	}

}

Vector2D SceneComponent::GetWorldScale() const
{
	if (parent)
		return parent->GetWorldScale() * GetLocalScale();
	else {
		if (pOwner)return pOwner->GetWorldScale();
		else return GetLocalScale();
	}
}






void Object::Update()
{
	components_iter = components.begin();
	while (components_iter != components.end())
	{
		(*components_iter)->Update();
		if (components_iter != components.end())components_iter++;
	}
}

void Object::BeginPlay()
{
	for (auto&it : components)
	{
		it->BeginPlay();
	}
}

void Object::AttachTo(Object* par)
{
	if (par) {
		par->children.insert(this);
		parent = par;
	}
}

void Object::DetachFrom(Object* par)
{
	if (par) {
		par->children.erase(this);
		parent = nullptr;
	}
}


void Object::Destroy()
{
	if(parent)parent->children.erase(this);

	std::stack<Object*>objects_to_delete;
	objects_to_delete.push(this);

	while (!objects_to_delete.empty()) {
		Object* current_object = objects_to_delete.top();
		objects_to_delete.pop();

		if (!current_object->children.empty())
		{
			for (auto& child : current_object->children)
			{
				objects_to_delete.push(child);
			}
		}
		mainWorld.GameObjects_to_delete.insert(current_object);
	}
}


Vector2D Object::GetWorldPosition() const
{
	if (parent)return parent->GetWorldPosition() + GetLocalPosition();
	else return GetLocalPosition();
}

float Object::GetWorldRotation() const
{
	if (parent)return parent->GetWorldRotation() + GetLocalRotation();
	else return GetLocalRotation();
}

Vector2D Object::GetWorldScale() const
{
	if (parent)return parent->GetWorldScale() * GetLocalScale();
	else return GetLocalScale();
}

void Object::DrawDebugPosition() const
{
	Vector2D pos = (GetWorldPosition() - mainWorld.mainCamera->transform_virtual.position)
		* 20.f / mainWorld.mainCamera->springArmLength_virtual
		+ Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	outtextxy((int)pos.x, (int)pos.y, GetWorldPosition().ToString().c_str());
}



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

	for (auto& obj : GameObjects)obj->Update();
	for (auto& obj : GameObjects_to_add)
	{
		GameObjects.insert(obj);
		obj->BeginPlay();
	}
	GameObjects_to_add.clear();
	for (auto& obj : GameObjects_to_delete) 
	{
		GameObjects.erase(obj);
		delete obj;
	}
	GameObjects_to_delete.clear();
	for (auto& obj : GameUIs)GameUIs.insert(obj);
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
}


void World::ProcessColliders() 
{
	for (auto& arr_i : ColliderZones)for (auto& arr_j : arr_i) if (!arr_j.empty())
		for (auto& me : arr_j)for (auto& he : arr_j) if (he != me) me->Insert(he);
	//碰撞插入信息更新

	for (auto& it : GameColliders)it->Erase();
	//碰撞删除信息更新
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
	mainController->PeekInfo();
}

void World::Update_()
{
	mainCamera->Calculate();
}

void World::Debug()
{	
	for (auto& obj : GameColliders)
		obj->DrawDebugLine();
	for (auto& obj : GameObjects)
		obj->DrawDebugPosition();

	static int FPS = 0;
	static int number = 0;
	number++;
	outtextxy(0, 0, (std::string("FPS: ") + std::to_string(FPS)).c_str());
	if (FPSClock->GetDelay() >= 1.0) {
		FPS = number;
		FPSClock->Reset();
		number = 0;
	}
}
