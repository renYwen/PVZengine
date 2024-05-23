#pragma once

#include <unordered_map>
#include <easyx.h>
#include <string>


struct AnimationResource
{
	IMAGE** images;
	int num;
};


//��Դ������
class ResourceManager
{
	std::unordered_map<std::string,IMAGE*>imagePool;
	std::unordered_map<std::string,AnimationResource>animationPool;

	void Load(std::string name, std::string path,int wid,int hei);//���ص���ͼƬ
	void Load(std::string name, std::string path, int wid, int hei,int num);//���ض��Ŷ���ͼƬ
	void Load(std::string name, std::string path, int wid, int hei, int num, int row, int col);//����SpriteSheet����ͼƬ
public:
	
	void Initialize();

	IMAGE* Fetch(std::string name);
	AnimationResource FetchAnimation(std::string name);
};