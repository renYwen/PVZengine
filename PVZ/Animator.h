#pragma once
#include"CoreMinimal.h"
#include"easyx.h"
#include"Timer.h"
#include<unordered_map>


//����Դ
class Animation
{
    friend class Animator;

	int num = 0;//����֡��
	Vector2D offset = {0,0};//ƫ����
	IMAGE**images = nullptr;//����֡����
	int index = 0;//��ǰ֡����

	Timer clock;//��ʱ��

public:
	Animation() { clock.Bind(0, [this](){index = (index + 1) % num; }, true); }

	void Load(std::string name, Vector2D delta = {0,0});

	void SetInterval(double interval) { clock.SetDelay(interval); }

	void SetIndex(int i) { index = i; }
};


//����������
class Animator final: public Component
{
	std::unordered_map<std::string, Animation&> animations;

	Animation* aniNode = nullptr;//��ǰ���ŵĶ���

	class SpriteRenderer* rendererAttached = nullptr;//���ŵ���Ⱦ��

public:
	virtual void BeginPlay() override;
	virtual void Update() override;

	void Insert(std::string name, Animation& ani);

	Animation* GetNode()const {return aniNode;}

	void SetNode(std::string nodeName);

	void SetCalled(bool called);
};