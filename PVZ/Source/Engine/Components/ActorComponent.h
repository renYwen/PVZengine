#pragma once
#include"CoreMinimal.h"


class Actor;


/* ������� */
class ActorComponent : public Object
{
public:
	//��ȡ����Ϸ����
	Actor* GetOwner();

	//���ð���Ϸ����
	void SetOwner(Actor* owner);

	//�������
	virtual void Destruct();

	//�������
	virtual void Activate();
	
	//ͣ�����
	virtual void Deactivate();

protected:
	Actor* pOwner = nullptr;//��������߼�

	bool bIsEnabled = true;//�Ƿ񼤻�
};