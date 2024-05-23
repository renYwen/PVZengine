#pragma once
#include"CoreMinimal.h"
#include"VisualInterface.h"



//äÖÈ¾Æ÷£¨2D£©
class SpriteRenderer final: public SceneComponent,public LayerInterface,public ImageInterface
{
	DEFINE_SUPER(SceneComponent)
	friend class Animator;
public:
	virtual ~SpriteRenderer() { ; }
	virtual void Render()override;
	virtual void Update()override;
};



