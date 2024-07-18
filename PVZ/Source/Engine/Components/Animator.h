#pragma once
#include"ActorComponent.h"
#include"Tools/Timer.h"
#include"Tools/Delegate.h"
#include<unordered_map>



/* ����ί�� */
DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(AnimationDelegate)


class IMAGE;

/* ����Դ */
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
	Animation() { clock.Bind(0, this, &Animation::Tick, true); clock.Stop();}

	void Load(std::string name, Vector2D delta = {0,0});

	//���ö���֡���ʱ��
	void SetInterval(double interval) { clock.SetDelay(interval); }

	//���ö���֡�±�
	void SetIndex(int i) { index = i; }

	//��ָ��֡����Ӷ���֪ͨ
	void AddNotification(int index, AnimationDelegate& event) { notifications.insert({ index,event }); }
};


class SpriteRenderer;

/* ���������� */
class Animator final: public ActorComponent
{
	DEFINE_SUPER(ActorComponent)

    friend SpriteRenderer;
public:
	virtual ~Animator();
	virtual void BeginPlay() override;
	virtual void Update() override;

	virtual void Activate()override;
	virtual void Deactivate()override;

	//���붯���ڵ�
	void Insert(std::string name, Animation& ani);

	//��ȡ��ǰ�����ڵ�
	Animation* GetNode()const;

	//���ö����ڵ�
	void SetNode(std::string nodeName);

	//���ø�����Ⱦ��
	void SetupAttachment(SpriteRenderer*renderer);
private:
	std::unordered_map<std::string, Animation&> animations;

	Animation* aniNode = nullptr;//��ǰ���ŵĶ���

	SpriteRenderer* rendererAttached = nullptr;//���ŵ���Ⱦ��

	IMAGE* currentSprite = nullptr;//��ǰ���ŵ�ͼ��
};