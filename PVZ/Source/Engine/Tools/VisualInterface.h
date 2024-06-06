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
};//��Ⱦ������Ϣ

struct FilterInfo 
{
	COLORREF color = BLACK;//�˾���ɫ
	int level = 50;//��ɫ���ɲ㼶��1~100��
	int layer = 0;//�˾��㼶��0��1��
};//�˾���Ϣ


//�˾�ͼ���������
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

	//�����˾�
	void SetFilter(bool enable, COLORREF col = BLACK, int level = 60);

    void AddFilter(FilterInfo filterInfo);
	void RemoveFilter();

	/* ���طǶ�����Դ */
	void LoadSprite(std::string name);

	/* �Ƽ����÷Ƕ�����Դ */
	void SetStartAndEndLoc(Pair start, Pair end);
};



