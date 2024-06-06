#pragma once
#include"CoreMinimal.h"
#include"Core/World.h"


class GameplayStatics final
{
public:
	//获取游戏实例
	static GameInstance* GetGameInstance();
	
	//获取玩家控制器
	static class Controller* GetController();

	//创建游戏对象
	template<typename T>
	static T* CreateObject(Vector2D pos = Vector2D(0, 0));

	//通过类查找游戏对象
	template<typename T>
	static std::vector<T*>FindObjectsOfClass();

	//通过标签名查找游戏对象
	template<typename T>
	static T* FindObjectOfName(std::string tagName);

	//创建UI对象
	template<class T>
	static T* CreateUI();

	//加载地图
	static void OpenLevel(std::string levelName);
};





template<typename T>
inline T* GameplayStatics::CreateObject(Vector2D pos)
{
	T* pObj = new T;
	if (pObj && static_cast<Actor*>(pObj)) 
	{
		mainWorld.GameActors_to_add.push_back(pObj);
		if(pos != Vector2D())pObj->SetLocalPosition(pos);
		return pObj;
	}
	delete pObj;
	return nullptr;
}

template<typename T>
inline std::vector<T*> GameplayStatics::FindObjectsOfClass()
{
	std::vector<T*> result;
	result.reserve(mainWorld.GameActors.size());
	for (auto& obj : mainWorld.GameActors) 
	{
		if (T* pObj = dynamic_cast<T*>(obj))result.push_back(pObj);
	}
	return result;
}

template<typename T>
inline T* GameplayStatics::FindObjectOfName(std::string tagName)
{
	for (auto& obj : mainWorld.GameActors)
	{
		if (obj->GetName() == tagName)return obj;
	}
	return nullptr;
}

template<class T>
inline T* GameplayStatics::CreateUI()
{
	T* pUI = new T;
	if (pUI && static_cast<UserInterface*>(pUI)) 
	{
		mainWorld.GameUIs.insert(pUI);
		return pUI;
	}
	delete pUI;
	return nullptr;
}

