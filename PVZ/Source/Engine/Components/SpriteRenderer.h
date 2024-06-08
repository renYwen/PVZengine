#pragma once
#include"Components/SceneComponent.h"
#include"Tools/VisualInterface.h"


class Animator;

//��Ⱦ����2D��
class SpriteRenderer final: public SceneComponent,public LayerInterface,public ImageInterface
{
	DEFINE_SUPER(SceneComponent)
	friend Animator;

	Animator* animatorAttached = nullptr;//���ŵĶ���������

	void DealImage();
public:
	virtual ~SpriteRenderer();
	virtual void Render()override;
	virtual void Update()override;
};



