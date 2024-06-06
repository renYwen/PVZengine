#pragma once
#include"CoreMinimal.h"


class ActorComponent;
class SceneComponent;


/* ����������� */
class Actor :public Object
{
	friend class RigidBody;

	std::unordered_set<Actor*>children;
	Actor* parent = nullptr;//���������Թ�ϵ ���� ������ɾ

	std::unordered_set<ActorComponent*>components;
	std::unordered_set<ActorComponent*>::iterator components_iter;//��������ı����Լ���ɾ

protected:
	SceneComponent* const root = nullptr;//��������������賡������
public:
	Actor();

	virtual ~Actor();

	virtual void Update()override;

	virtual void BeginPlay()override;

	//���ó��������
	void SetRootComponent(SceneComponent* newRoot);

	//������������
	void AttachTo(Actor* par);

	//�����������
	void DetachFrom(Actor* par);


	//�����ע�ᵽ��������
	void RegisterComponent(ActorComponent* pCom);

	//�Ӷ���������ע�����
	void UnregisterComponent(ActorComponent* pCom);

	//������Ϸ����
	void Destroy();

	//��ȡ�������ԣ���Ը���������ϵ��
	const Vector2D& GetLocalPosition() const;
	float GetLocalRotation() const;
	const Vector2D& GetLocalScale() const;

	//��ȡ�������ԣ������������ϵ��
	Vector2D GetWorldPosition()const;
	float GetWorldRotation()const;
	Vector2D GetWorldScale()const;

	//���ó������ԣ���Ը���������ϵ��
	void SetLocalPosition(const Vector2D& pos);
	void SetLocalRotation(float angle);
	void SetLocalScale(const Vector2D& scale);

	//���ӳ�������ƫ����
	void AddPosition(Vector2D pos);
	void AddRotation(float rot);

	//����λ����Ϣ
	void DrawDebugPosition() const;

	//�������,�󶨵�����,��ע�ᵽ��������
	template<typename T>
	T* ConstructComponent()
	{
		T* pCom = new T;
		if (pCom && static_cast<ActorComponent*>(pCom))
		{
			pCom->SetOwner(this);
			RegisterComponent(pCom);
			return pCom;
		}
		delete pCom;
		return nullptr;
	}

	//ͨ��������ȡ���
	template<typename T>
	T* GetComponentByClass()
	{
		for (auto& com : components)
		{
			if (T* pCom = dynamic_cast<T*>(com))return pCom;
		}
		return nullptr;
	}
};

