#pragma once
#include"CoreMinimal.h"



//��������
class Camera final:public SceneComponent
{
	friend class SpriteRenderer;
	friend class Particle;
	friend class CircleCollider;
	friend class BoxCollider;
	friend class World;
	friend void Object::DrawDebugPosition()const;
public:
	virtual void Update()override;

	virtual void BeginPlay()override;

	//�����������
	void SetMainCamera()
	{
 	    mainWorld.mainCamera = this;
	}

	//��������ƶ�ƽ����
	void SetSmoothness(int smooth);

	//���þ�����ֵ
	void SetDistanceThreshold(float threshold);

	//����������ɳ���
	void SetSpringArmLength(float length);

	//�����������ƽ����
	void SetSpringArmSmoothness(int smooth);

	//�����
	void ShakeCamera(int intensity,int decay = 20);

private:
	Transform transform_virtual;//�������λ��


	float distanceThreshold = 100.f;//������ֵ0`500
	int smoothness = 30;//ƽ����0~100


	float shakeIntensity = 0;//��ǿ��0~100
	bool shakeFlag = false;//�𶯱�־λ
	Vector2D shakeCenter = Vector2D();//������
	Vector2D shakeSpeed = Vector2D(0.05f, 0.05f);//���ٶ�
	int shakeDecay = 5;//��˥��ϵ��1`100

	float springArmLength = 20.f;//���ɳ���1~10000
	float springArmLength_virtual = 100.f;//���ⵯ�ɳ���
	int smoothnessForSpringArm = 20;//����ƽ����0~100


	Vector2D Lerp(Vector2D start, Vector2D end, float t);//���Բ�ֵ��Vector2D��
	float Lerp(float start, float end, float t);//���Բ�ֵ��float��

	float SmoothStep(float x);//ƽ������

	void Calculate();
};