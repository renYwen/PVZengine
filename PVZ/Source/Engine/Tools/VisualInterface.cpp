#include "VisualInterface.h"
#include "ResourceManager.h"
#include "Math.h"



LayerInterface::LayerInterface()
{
	mainWorld.GameRenderers.insert(this);
}

LayerInterface::~LayerInterface()
{
	mainWorld.GameRenderers.erase(this);
}

void LayerInterface::SetLayer(int layer)
{
	mainWorld.GameRenderers.erase(this);
	this->layer = layer;
	mainWorld.GameRenderers.insert(this);
}

int LayerInterface::GetLayer()const
{
	return layer;
}

void ImageInterface::RotateImage(double radian)
{			
	radian = -radian;
	float fSin = (float)sin(radian), fCos = (float)cos(radian);				
	int w = sprite->getwidth(), h = sprite->getheight();
	POINT points[4] = { {0, 0}, {w, 0}, {0, h}, {w, h} };	
	int min_x = 0, min_y = 0;
	int max_x = 0, max_y = 0;
	for (int i = 0; i < 4; i++)											
	{
		points[i] = {
			(int)(points[i].x * fCos - points[i].y * fSin),
			(int)(points[i].x * fSin + points[i].y * fCos)
		};
		min_x = MIN(min_x, points[i].x);
		min_y = MIN(min_y, points[i].y);
		max_x = MAX(max_x, points[i].x);
		max_y = MAX(max_y, points[i].y);
	}
	
	int nw = max_x - min_x;							
	int nh = max_y - min_y;
	int nSize = nw * nh;
	

	if(!copy)copy = new IMAGE(nw, nh);
	copy->Resize(nw, nh);
	spriteInfo.endLoc = {nw, nh};

	DWORD* pNewBuf = GetImageBuffer(copy);
	const DWORD* pBuf = GetImageBuffer(sprite);

	for (int i = min_x, ni = 0; ni < nw; ++i, ++ni)						// i 用于映射原图像坐标，ni 用于定位旋转后图像坐标
	{
		for (int j = min_y, nj = 0; nj < nh; ++j, ++nj)
		{
			pNewBuf[nj * nw + ni] = 0;
			int nx = (int)(i * fCos + j * fSin);							// 从旋转后的图像坐标向原图像坐标映射
			int ny = (int)(-i * fSin + j * fCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)				// 若目标映射在原图像范围内，则拷贝色值
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
		}
	}
}

void ImageInterface::FilterImage()
{
	IMAGE* img = copy ? copy : sprite;
	if (!filter)filter = new IMAGE(img->getwidth(), img->getheight());
	filter->Resize(img->getwidth(), img->getheight());

	const DWORD* pBuf = GetImageBuffer(img);
	DWORD* pNewBuf = GetImageBuffer(filter);
	int num = img->getheight() * img->getwidth();

	for (int i = 0; i < num; ++i)
	{
		if (pBuf[i]>>24)
		{
			// 获取BGR
			uint32 pNewBufB = pBuf[i] & 0xFF;
			uint32 pNewBufG = (pBuf[i] & 0xFF00) >> 8;
			uint32 pNewBufR = (pBuf[i] & 0xFF0000) >> 16;

			// 将颜色值进行平均化
			for (auto& filterInfo : filterLayers) 
			{
				int level = filterInfo.level;
				if(pBuf[i]>>24 < 250)level = (pBuf[i] >> 24)*level>>8;//使得颜色滤镜从低透明度到高透明度平滑过渡
				pNewBufB = (pNewBufB * (128 - level) + level * GetBValue(filterInfo.color))>>7;
				pNewBufG = (pNewBufG * (128 - level) + level * GetGValue(filterInfo.color))>>7;
				pNewBufR = (pNewBufR * (128 - level) + level * GetRValue(filterInfo.color))>>7;
			}
			// 重新组合成一个新的颜色值（BGR）
			pNewBuf[i] = (pBuf[i] & 0xFF000000) | (pNewBufR << 16) | (pNewBufG << 8) | pNewBufB;
		}
		else pNewBuf[i] = 0;
	}

}

void ImageInterface::SetFilter(bool enable,COLORREF col, int level)
{
	filterLayers.erase(FilterInfo{ col, level});
	if (enable) 
	{
		level = Math::Clamp(level, 0, 100);
		filterLayers.insert(FilterInfo{ col, level});
		FilterImage();
	}
}

void ImageInterface::AddFilter(FilterInfo filterInfo)
{
	filterLayers.insert(filterInfo);
	FilterImage();
}

void ImageInterface::RemoveFilter()
{
	filterLayers.erase({BLACK,60,1});
}

void ImageInterface::LoadSprite(std::string name)
{
	sprite = mainWorld.resourcePool->Fetch(name); 
    spriteInfo.endLoc = { sprite->getwidth(), sprite->getheight() };
}

void ImageInterface::SetStartAndEndLoc(Pair start, Pair end)
{
	start.x = Math::Clamp(start.x, 0, spriteInfo.size.x);
    start.y = Math::Clamp(start.y, 0, spriteInfo.size.y);
    end.x = Math::Clamp(end.x, 0, spriteInfo.size.x);
    end.y = Math::Clamp(end.y, 0, spriteInfo.size.y);
    spriteInfo.startLoc = start;
    spriteInfo.endLoc = end;
}
