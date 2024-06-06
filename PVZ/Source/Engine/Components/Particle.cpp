#include"Particle.h"
#include"Camera.h"
#include"ResourceManager.h"
#include"Tools/Math.h"




void Particle::Produce()
{
	ParticleInfo temp;
	temp.alpha = alpha;
	temp.index = Math::RandInt(0, number - 1);
	if (pattern == ParticlePattern::Center)
	{
		double radian = -Math::RandReal(scoop.x, scoop.y) * PI / 180;
		unitVector = Vector2D((float)cos(radian), (float)sin(radian));
		if(radius!=Vector2D(0,0))temp.offset = unitVector *  
			float((min(radius.x,radius.y) + std::abs(radius.y-radius.x) * Math::RandPerc()));
		temp.velocity = speed * unitVector;
	}
	else
	{
		double radian = -angle * PI / 180;
		unitVector = Vector2D((float)cos(radian), (float)sin(radian));
		Vector2D lineVector = Vector2D::RotateVector(90, unitVector);
		if(length)temp.offset = lineVector * (float)(-length/2 + length * Math::RandPerc());
		temp.velocity = speed * lineVector;
	}
	particles.push_back(temp);
}

void Particle::Load(std::string name)
{
	AnimationResource aniRes = mainWorld.resourcePool->FetchAnimation(name);
	number = aniRes.num;
	images = aniRes.images;
}


void Particle::Update()
{
	SceneComponent::Update();

	if (particles.size() < capacity)
	{
		if(interval == 0)for (int i = 0; i < capacity; i++)Produce();
		else if(duration<float>(steady_clock::now() - lastTime).count() >= interval)
		{
			Produce();lastTime = steady_clock::now();
		}

		if (!isLoop && particles.size() >= capacity)capacity = -1;
	}//生产管理


	if (particles.size()) 
	{
		if (interval == 0) 
		{
			if (duration<float>(steady_clock::now() - particles.begin()->lastTime).count() >= lifeCycle)
			{
				particles.clear();
			}
			else if (fadingTime && duration<float>(steady_clock::now() - particles.begin()->lastTime).count() 
				>= lifeCycle - fadingTime)
			{
				for (auto &each : particles)each.alpha -= alpha * DELTA_TIME / fadingTime;
			}
		}
		else if (duration<float>(steady_clock::now() - particles.begin()->lastTime).count() >= lifeCycle) 
		{
			particles.pop_front();
		}
	}//销毁逻辑

	for (auto &each : particles)
	{
		if(graivity)each.velocity.y += graivity * DELTA_TIME;
		each.offset += each.velocity * DELTA_TIME;
		if (fadingTime && duration<float>(steady_clock::now() - each.lastTime).count()
			>= lifeCycle - fadingTime)
		{
			each.alpha -= alpha * DELTA_TIME / fadingTime;
		}
	}//粒子参数管理
}

void Particle::Render()
{
	if (images) 
	{
		Vector2D center = (GetWorldPosition() - mainWorld.mainCamera->transform_virtual.position);
		HDC dstDC = GetImageHDC();

		
		int w = images[0]->getwidth();
		int h = images[0]->getheight();
		float dw = float(w * GetWorldScale().x * 20.f / mainWorld.mainCamera->springArmLength_virtual);
		float dh = float(h * GetWorldScale().y * 20.f / mainWorld.mainCamera->springArmLength_virtual);

		for (auto& each : particles) 
		{
			BLENDFUNCTION bf = { AC_SRC_OVER,0,(BYTE)(each.alpha>0?each.alpha:0),AC_SRC_ALPHA };
			Vector2D pos = center + each.offset;
			pos = pos * 20.f / mainWorld.mainCamera->springArmLength_virtual
				+ Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2) - Vector2D(dw / 2, dh / 2);
			HDC srcDC = GetImageHDC(images[each.index]);
			AlphaBlend(dstDC, (int)pos.x, (int)pos.y, (int)dw,(int)dh, srcDC, 0, 0, w, h, bf);
		}
	}
}


