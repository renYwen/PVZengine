#pragma once
#include"Components/InputComponent.h"
#include"Actor.h"


class Camera;
struct HitResult;


//��ҿ�������
class Controller :public Actor
{
	DEFINE_SUPER(Actor)

	InputComponent* inputComponent;
	Camera* camera;

protected:
	virtual void SetupInputComponent(InputComponent* inputComponent) {}
public:
	Controller();

	virtual void BeginPlay() override;

	void PeekInfo();

	//��ȡ�����������ϵλ��
	Vector2D GetCursorPosition() const;

	//��ȡ����Ƿ���
	bool IsMouseClicked() const;

	//��ȡ��������ϵ���������λ������������Ϣ�����������ӵ����ײ�壩
	HitResult GetHitResultUnderCursor();

	//�����������
	void EnableInput(bool enable);
};