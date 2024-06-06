#include "CollisionManager.h"




void CollisionManager::Initialize()
{
	/* ��ײ���� */
	AddMapping(CollisionType::Bullet,CollisionType::Zombie);
	AddMapping(CollisionType::Plant, CollisionType::Zombie);
}





CollisionManager::CollisionManager()
{
	collisionMap.insert({ int(CollisionType::Default) * int(CollisionType::Default) + int(CollisionType::Default) * int(CollisionType::Default) });
}


bool CollisionManager::FindMapping(CollisionType type1, CollisionType type2)
{
	int result = int(type1) * int(type1) + int(type2) * int(type2);
	return collisionMap.find(result)!= collisionMap.end();
}

void CollisionManager::AddMapping(CollisionType type1, CollisionType type2)
{
	int result = int(type1) * int(type1) + int(type2) * int(type2);
	collisionMap.insert(result);
}