#pragma once
#include"CoreMinimal.h"
#include<easyx.h>
#include<string>



class LayerInterface
{
	int layer = 0;
public:
	LayerInterface();
	virtual ~LayerInterface();
	void SetLayer(int layer);
	int GetLayer()const;

	virtual void Render() = 0;
};


struct SpriteInfo
{
	Vector2D offset = Vector2D(0, 0);
	Pair size = Pair(0, 0);
	Pair startLoc = Pair(0, 0);
	Pair endLoc = Pair(0, 0);
};//渲染补充信息

struct FilterInfo 
{
	COLORREF color = BLACK;//滤镜颜色
	int level = 50;//颜色过渡层级（1~100）
	int layer = 0;//滤镜层级（0和1）
};//滤镜信息


//滤镜图层排序规则
struct FilterSort
{
	bool operator()(const FilterInfo& a, const FilterInfo& b) const
	{
        return a.layer < b.layer;
	}
};


class ImageInterface
{
protected:
	IMAGE* sprite = nullptr;
	SpriteInfo spriteInfo;
	BYTE alpha = 255;

	IMAGE* copy = nullptr;
	float angle = 0;
	void RotateImage(double radian);

	IMAGE* filter = nullptr;
	std::set<FilterInfo, FilterSort>filterLayers;
	void FilterImage();
public:
	virtual ~ImageInterface() { if (copy)delete copy; if (filter)delete filter; }

	BYTE GetTransparency()const { return alpha; }
	void SetTransparency(BYTE tranparency) {alpha = tranparency; }

	//设置滤镜
	void SetFilter(bool enable, COLORREF col = BLACK, int level = 60);

    void AddFilter(FilterInfo filterInfo);
	void RemoveFilter();

	/* 加载非动画资源 */
	void LoadSprite(std::string name);

	/* 推荐设置非动画资源 */
	void SetStartAndEndLoc(Pair start, Pair end);
};



