#include "SpriteRenderer.h"
#include "Camera.h"
#include "Core/World.h"
#pragma comment(lib,"Msimg32.lib")


void SpriteRenderer::DealImage()
{
	if (GetWorldRotation() != angle)
	{
		angle = GetWorldRotation();
		RotateImage(PI * angle / 180);
	}
	if (filterLayers.size() > 0)FilterImage();
}

void SpriteRenderer::Render()
{
	if (!sprite)return;

	Vector2D pos = (GetWorldPosition() - mainWorld.mainCamera->transform_virtual.position + spriteInfo.offset) 
		* 20.f / mainWorld.mainCamera->springArmLength_virtual + Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	HDC dstDC = GetImageHDC();

	IMAGE* img = copy ? copy : sprite;
	HDC srcDC = GetImageHDC(img);
	int w = spriteInfo.endLoc.x - spriteInfo.startLoc.x;
	int h = spriteInfo.endLoc.y - spriteInfo.startLoc.y;

	float multi_w = GetWorldScale().x * 20.f / mainWorld.mainCamera->springArmLength_virtual;
	float multi_h = GetWorldScale().y * 20.f / mainWorld.mainCamera->springArmLength_virtual;

	BLENDFUNCTION bf = { AC_SRC_OVER,0,alpha,AC_SRC_ALPHA };
	if (filterLayers.size() > 0 && filter)srcDC = GetImageHDC(filter);
	AlphaBlend(dstDC, (int)pos.x - int(multi_w * img->getwidth() / 2), (int)pos.y - int(multi_h * img->getheight() / 2),
		int(w * multi_w), int(h * multi_h),srcDC,(int)spriteInfo.startLoc.x, (int)spriteInfo.startLoc.y, w, h, bf);
}

void SpriteRenderer::Update()
{
	SceneComponent::Update();
	if (!sprite)return;

	if (copy)spriteInfo.size = Pair(copy->getwidth(), copy->getheight());
	else spriteInfo.size = Pair(sprite->getwidth(), sprite->getheight());

	if (GetWorldRotation() != angle)
	{
		angle = GetWorldRotation();
		RotateImage(PI * angle / 180);
		if (filterLayers.size() > 0)FilterImage();
	}
}



