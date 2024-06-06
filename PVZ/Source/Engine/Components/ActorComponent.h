#pragma once
#include"CoreMinimal.h"


class Actor;


/* ������� */
class ActorComponent : public Object
{
protected:
	Actor* pOwner = nullptr;//��������߼�
public:
	virtual void Update() {}

	virtual void BeginPlay() {}

	//���ð󶨶���
	void SetOwner(Actor* owner);

	//�������
	virtual void Destruct();
};