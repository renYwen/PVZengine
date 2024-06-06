#pragma once
#include"CoreMinimal.h"
#include<unordered_map>
#include<string>




//µÿÕºπ‹¿Ì∆˜
class LevelManager
{
public:
	void Initialize();

	void SetDefaultLevel(std::string levelName);

	void RefreshLevel();
private:
	std::unordered_map<std::string, class Level*>levelMap;

	template<class T>
	void AddLevel(std::string levelName);

	Level* level_to_delete = nullptr;
};

template<class T>
inline void LevelManager::AddLevel(std::string levelName)
{
	T* pLevel = new T;
	if (pLevel && static_cast<Level*>(pLevel))
	{
		levelMap.insert({levelName,pLevel});
		return;
	}
	delete pLevel;
}
