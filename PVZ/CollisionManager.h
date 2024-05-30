#pragma once
#include <unordered_set>

//碰撞类型
enum class CollisionType:uint8_t
{
	Default,
	Plant,
	Bullet,
	Zombie
};

//碰撞管理器
class CollisionManager
{
	std::unordered_set<int>collisionMap;

public:
	CollisionManager()
	{
		collisionMap.insert({ int(CollisionType::Default) * int(CollisionType::Default) + int(CollisionType::Default) * int(CollisionType::Default) });
	}

	void Initialize();

	bool FindMapping(CollisionType type1, CollisionType type2);

	void AddMapping(CollisionType type1, CollisionType type2);
};