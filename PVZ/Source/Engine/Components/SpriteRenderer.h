#pragma once
#include"Components/SceneComponent.h"
#include"Tools/VisualInterface.h"


class Animator;

//äÖÈ¾Æ÷£¨2D£©
class SpriteRenderer final: public SceneComponent,public LayerInterface,public ImageInterface
{
	DEFINE_SUPER(SceneComponent)
	friend Animator;

	Animator* animatorAttached = nullptr;//¸½×ÅµÄ¶¯»­²¥·ÅÆ÷

	void DealImage();
public:
	virtual ~SpriteRenderer();
	virtual void Render()override;
	virtual void Update()override;
};



