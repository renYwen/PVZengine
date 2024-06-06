#pragma once
#include"CoreMinimal.h"
#include"Tools/Timer.h"
#include"Tools/Delegate.h"
#include"easyx.h"
#include<unordered_map>



//����ί��
DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(AnimationDelegate)


//����Դ
class Animation final
{
    friend class Animator;

	int num = 0;//����֡��
	Vector2D offset = {0,0};//ƫ����
	IMAGE**images = nullptr;//����֡����
	int index = 0;//��ǰ֡����

	Timer clock;//��ʱ��

	std::unordered_map<int, AnimationDelegate>notifications;//�Զ��嶯��֪ͨ

	void Tick();

public:
	Animation() { clock.Bind(0, this, &Animation::Tick, true); clock.Stop(); }

	void Load(std::string name, Vector2D delta = {0,0});

	//���ö���֡���ʱ��
	void SetInterval(double interval) { clock.SetDelay(interval); }

	//�����±�
	void SetIndex(int i) { index = i; }

	//��ָ��֡����Ӷ���֪ͨ
	void AddNotification(int index, AnimationDelegate& event) { notifications.insert({ index,event }); }
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

	//���ö����ڵ�
	void SetNode(std::string nodeName);

	//���ö����Ƿ񲥷�
	void SetCalled(bool called);
};