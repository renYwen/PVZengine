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



//��Ⱦͼ���������
struct LayerSort
{
	bool operator()(const LayerInterface* a, const LayerInterface* b) const;
};
//��ײͼ���������
struct ColliderSort
{
	bool operator()(const Collider* a, const Collider* b) const;
};


/* ��Ϸ���� */
class World final
{
	/* ��Ԫ���� */
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

	/* ��Դ�� */
	ResourceManager* resourcePool = nullptr;

	/* ��ײ������ */
	CollisionManager* collisionManager = nullptr;

	/* ��ͼ������ */
	LevelManager* levelManager = nullptr;

	/* ȫ�ּ�ʱ�� */
	Timer* FPSClock = nullptr;


	/* ��������UI����ʱ������ */
	std::unordered_set<Actor*>GameActors;
	std::vector<Actor*>GameActors_to_add;
	std::unordered_set<Actor*>GameActors_to_delete;
	std::unordered_set<UserInterface*>GameUIs;
	std::unordered_set<UserInterface*>GameUIs_to_delete;
	std::unordered_set<Timer*>GameTimers;


	/*  ��Ⱦ����ײ���㡢UI��������� */
	std::set<LayerInterface*, LayerSort>GameRenderers;
	std::unordered_set<Collider*>GameColliders;
	std::unordered_set<Collider*>GameColliders_to_clear;
	std::set<Collider*, ColliderSort>ColliderZones[8][6];
	std::set<LayerInterface*, LayerSort>UIDetectZones[8][6];

	/* ��Ϸ�������� */
	GameInstance* gameInstance = nullptr;

	Level* currentLevel = nullptr;

	Camera* mainCamera = nullptr;


	/* �����߼����� */
	void Update();//�߼�����

	void Update_();//�߾��ȼ���

	void Render();//��Ⱦ

	void Input();//��������

	void ProcessColliders();//��ײ����

	/* Debugģʽ */
	void Debug();


	/* ������� */
	void WipeData();
};


extern World mainWorld;