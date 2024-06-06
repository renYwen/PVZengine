#pragma once
#include"CoreMinimal.h"
#include"Objects/Actor.h"



class Engine;
class LevelManager;
class ResourceManager;
class CollisionManager;
class GameplayStatics;
class Timer;
class LayerInterface;
class ImageInterface;
class UserInterface;
class Widget;
class Button;
class Bar;
class Camera;
class SpriteRenderer;
class Animation;
class Particle;
class Collider;
class CircleCollider;
class BoxCollider;
class Controller;



//渲染图层排序规则
struct LayerSort
{
	bool operator()(const LayerInterface* a, const LayerInterface* b) const;
};
//碰撞图层排序规则
struct ColliderSort
{
	bool operator()(const Collider* a, const Collider* b) const;
};


/* 游戏世界 */
class World final
{
	/* 友元声明 */
	friend Engine;
	friend GameplayStatics;
	friend Timer;
	friend LayerInterface;
	friend void Actor::Destroy();
	friend void Actor::DrawDebugPosition()const;
	friend ImageInterface;
	friend Camera;
	friend SpriteRenderer;
	friend Animation;
	friend Particle;
	friend Collider;
	friend CircleCollider;
	friend BoxCollider;
	friend Controller;
	friend UserInterface;
	friend Widget;
	friend Button;
	friend Bar;
	friend LevelManager;

	/* 资源池 */
	ResourceManager* resourcePool = nullptr;

	/* 碰撞管理器 */
	CollisionManager* collisionManager = nullptr;

	/* 地图管理器 */
	LevelManager* levelManager = nullptr;

	/* 全局计时器 */
	Timer* FPSClock = nullptr;


	/* 场景对象、UI、计时器容器 */
	std::unordered_set<Actor*>GameActors;
	std::vector<Actor*>GameActors_to_add;
	std::unordered_set<Actor*>GameActors_to_delete;
	std::unordered_set<UserInterface*>GameUIs;
	std::unordered_set<UserInterface*>GameUIs_to_delete;
	std::unordered_set<Timer*>GameTimers;


	/*  渲染、碰撞计算、UI鼠标检测容器 */
	std::set<LayerInterface*, LayerSort>GameRenderers;
	std::unordered_set<Collider*>GameColliders;
	std::unordered_set<Collider*>GameColliders_to_clear;
	std::set<Collider*, ColliderSort>ColliderZones[8][6];
	std::set<LayerInterface*, LayerSort>UIDetectZones[8][6];

	/* 游戏单例对象 */
	GameInstance* gameInstance = nullptr;

	Level* currentLevel = nullptr;

	Camera* mainCamera = nullptr;


	/* 核心逻辑遍历 */
	void Update();//逻辑处理

	void Update_();//高精度计算

	void Render();//渲染

	void Input();//交互处理

	void ProcessColliders();//碰撞计算

	/* Debug模式 */
	void Debug();


	/* 清空数据 */
	void WipeData();
};


extern World mainWorld;