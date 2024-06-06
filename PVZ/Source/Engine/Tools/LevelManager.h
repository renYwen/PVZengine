#pragma once
#include <unordered_map>
#include <string>


class Level;

/* ��ͼ������ */
class LevelManager
{
public:
	void Initialize();

	void SetDefaultLevel(std::string levelName);

	void RefreshLevel();
private:
	std::unordered_map<std::string, Level*>levelMap;

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
