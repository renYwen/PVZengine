#pragma once
#include"CoreMinimal.h"



//摄像机组件
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

	//设置主摄像机
	void SetMainCamera()
	{
 	    mainWorld.mainCamera = this;
	}

	//设置相机移动平滑度
	void SetSmoothness(int smooth);

	//设置距离阈值
	void SetDistanceThreshold(float threshold);

	//设置相机弹簧长度
	void SetSpringArmLength(float length);

	//设置相机弹簧平滑度
	void SetSpringArmSmoothness(int smooth);

	//相机震动
	void ShakeCamera(int intensity,int decay = 20);

private:
	Transform transform_virtual;//虚拟相机位置


	float distanceThreshold = 100.f;//距离阈值0`500
	int smoothness = 30;//平滑度0~100


	float shakeIntensity = 0;//震动强度0~100
	bool shakeFlag = false;//震动标志位
	Vector2D shakeCenter = Vector2D();//震动中心
	Vector2D shakeSpeed = Vector2D(0.05f, 0.05f);//震动速度
	int shakeDecay = 5;//震动衰减系数1`100

	float springArmLength = 20.f;//弹簧长度1~10000
	float springArmLength_virtual = 100.f;//虚拟弹簧长度
	int smoothnessForSpringArm = 20;//弹簧平滑度0~100


	Vector2D Lerp(Vector2D start, Vector2D end, float t);//线性插值（Vector2D）
	float Lerp(float start, float end, float t);//线性插值（float）

	float SmoothStep(float x);//平滑处理

	void Calculate();
};