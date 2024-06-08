#include "Camera.h"
#include "Core/World.h"
#include "Tools/Math.h"
#include "easyx.h"


Vector2D Camera::Lerp(Vector2D start, Vector2D end, float t)
{
	t = Math::Clamp(t, 0.001f, 0.1f);
	return start + (end - start) * t;
}

float Camera::Lerp(float start, float end, float t)
{
	t = Math::Clamp(t, 0.001f, 0.1f);
	return start + (end - start) * t;
}

float Camera::SmoothStep(float x)
{
	x = x<1?1:x;
	return pow(x, float(smoothness) / 100);
}


void Camera::BeginPlay()
{
	SceneComponent::BeginPlay();

	transform_virtual.position = GetWorldPosition();
	transform_virtual.rotation = GetWorldRotation();
	springArmLength_virtual = springArmLength;
	//初始化虚拟参数
}

void Camera::SetMainCamera()
{
	mainWorld.mainCamera = this;
}

void Camera::SetSmoothness(int smooth)
{
	this->smoothness = Math::Clamp(smooth, 0, 100);
}

void Camera::SetDistanceThreshold(float threshold)
{
	this->distanceThreshold = Math::Clamp(threshold, 0.f, 500.f);
}

void Camera::SetSpringArmLength(float length)
{
	this->springArmLength = Math::Clamp(length, 1.f, 10000.f);
}

void Camera::SetSpringArmSmoothness(int smooth)
{
	this->smoothnessForSpringArm = Math::Clamp(smooth, 0, 100);
}

void Camera::ShakeCamera(int intensity,int decay)
{
	intensity = Math::Clamp(intensity, 0, 100);
	decay = Math::Clamp(decay, 1, 100);
	shakeIntensity = (float)intensity;
	shakeDecay = decay;
	if (!shakeFlag)shakeCenter = GetLocalPosition();
	shakeFlag = true;
}

void Camera::Calculate()
{
	if (!bIsEnabled)return;

	if (smoothness)
	{
		transform_virtual.position = Lerp(transform_virtual.position, GetWorldPosition(),
			0.1f / smoothness * SmoothStep(Vector2D::Distance(transform_virtual.position, GetWorldPosition()) / distanceThreshold));
	}
	else transform_virtual.position = GetWorldPosition();
	//平滑位移

	if (smoothnessForSpringArm)springArmLength_virtual = Lerp(springArmLength_virtual, springArmLength, 0.1f/smoothnessForSpringArm);
	else springArmLength_virtual = springArmLength;
	//平滑视野缩放

	
	if (shakeFlag)
	{
		if (GetLocalPosition() == shakeCenter)
		{
			shakeSpeed.x = float(Math::RandInt(-1, 1));
			shakeSpeed.y = float(Math::RandInt(-1, 1));
			shakeIntensity -= float(shakeDecay) / 100;

			if (shakeIntensity <= 0) { shakeFlag = false; return; }
		}


		if (Vector2D::Distance(GetLocalPosition(), shakeCenter) < shakeIntensity)
		{
			AddPosition(shakeSpeed); transform_virtual.position += shakeSpeed;
		}
		else 
		{
			shakeSpeed = -shakeSpeed; AddPosition(shakeSpeed); transform_virtual.position += shakeSpeed;
		}
	}
	//相机抖动
}
