#pragma once

#include <unordered_map>
#include <easyx.h>
#include <string>


struct AnimationResource
{
	IMAGE** images;
	int num;
};


//资源管理器
class ResourceManager
{
	std::unordered_map<std::string,IMAGE*>imagePool;
	std::unordered_map<std::string,AnimationResource>animationPool;

	void Load(std::string name, std::string path,int wid,int hei);//加载单张图片
	void Load(std::string name, std::string path, int wid, int hei,int num);//加载多张动画图片
	void Load(std::string name, std::string path, int wid, int hei, int num, int row, int col);//加载SpriteSheet动画图片
public:
	
	void Initialize();

	IMAGE* Fetch(std::string name);
	AnimationResource FetchAnimation(std::string name);
};