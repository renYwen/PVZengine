#include "CollisionManager.h"


void CollisionManager::Initialize()
{
	/* Åö×²±í½¨Á¢ */
	AddMapping(CollisionType::Bullet,CollisionType::Zombie);
	AddMapping(CollisionType::Plant, CollisionType::Zombie);
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

