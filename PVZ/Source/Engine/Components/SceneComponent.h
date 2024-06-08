#pragma once
#include"Components/ActorComponent.h"



/* ����������� */
class SceneComponent : public ActorComponent
{
	Transform transform_local;
	std::unordered_set<SceneComponent*>children;
	SceneComponent* parent = nullptr;//���������Թ�ϵ��������ɾ

	void process_Destruct();

public:
	//�����������
	void AttachTo(SceneComponent* par);

	//����������
	void DetachFrom(SceneComponent* par);

	//�������
	virtual void Destruct() override;

	//��ȡ�������ԣ���Ը���������ϵ��
	const Vector2D& GetLocalPosition() const { return transform_local.position; }
	float GetLocalRotation() const { return transform_local.rotation; }
	const Vector2D& GetLocalScale() const { return transform_local.scale; }

	//��ȡ�������ԣ������������ϵ��
	Vector2D GetWorldPosition() const;
	float GetWorldRotation() const;
	Vector2D GetWorldScale() const;

	//���ó������ԣ���Ը���������ϵ��
	void SetLocalPosition(const Vector2D& pos) { transform_local.position = pos; }
	void SetLocalRotation(float angle) { transform_local.rotation = angle; }
	void SetLocalScale(const Vector2D& scale) { transform_local.scale = scale; }

	//���ӳ�������ƫ����
	void AddPosition(Vector2D pos) { transform_local.position += pos; }
	void AddRotation(float rot) { transform_local.rotation += rot; }
};
