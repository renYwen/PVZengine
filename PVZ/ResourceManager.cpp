#include "ResourceManager.h"


void ResourceManager::Initialize()
{
	/* ͼ����Դ���� */

	Load("bg0", "res/images/bg0.jpg", 1400, 600);

	Load("sunshine", "res/animations/bullets/sun", 78, 78, 22);

	Load("sunshine_1", "res/animations/bullets/sun.png", 483, 160, 12, 2, 6);

	




	//ֲ�ﶯ����Դ
	Load("peashooter", "res/animations/plants/peashooter.png", 483, 320, 24, 4, 6);

	Load("sunflower", "res/animations/plants/sunflower.png", 483, 320, 24, 4, 6);



	//�ӏ��YԴ
	Load("pea", "res/animations/bullets/pea.png",28,28);


	//��ʬ�YԴ
	Load("normalwalk", "res/animations/zombies/normal/walk.png", 1000, 695, 46, 5, 10);

	Load("normaleat", "res/animations/zombies/normal/eat.png", 1000, 556, 39, 4, 10);

	Load("zombiedie", "res/animations/zombies/die.png", 166, 1440, 10, 10, 1);
}





void ResourceManager::Load(std::string name, std::string path, int wid, int hei)
{
	IMAGE* img = new IMAGE;
	loadimage(img, LPCTSTR(path.c_str()),wid,hei);
	imagePool.insert({name, img});
}

void ResourceManager::Load(std::string name, std::string path, int wid, int hei, int num)
{
	IMAGE**images = new IMAGE*[num];
	for (int i = 0; i < num; i++)
	{
		images[i] = new IMAGE;
		loadimage(images[i], LPCTSTR((path+"/"+std::to_string(i)+".png").c_str()), wid, hei);
	}
	animationPool.insert({ name, {images,num } });
}

void ResourceManager::Load(std::string name, std::string path, int wid, int hei, int num, int row, int col)
{
	IMAGE**images = new IMAGE*[num];
	IMAGE img;
	loadimage(&img, LPCTSTR(path.c_str()), wid, hei);
	DWORD* src = GetImageBuffer(&img);

	int width = wid / col;
	int height = hei / row;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int x = j * width;
			int y = i * height;
			int index = i * col + j;
			if (index >= num)break;
			images[index] = new IMAGE(width,height);
			DWORD* dst = GetImageBuffer(images[index]);

			for (int x1 = 0; x1 < width; ++x1)
				for (int y1 = 0; y1 < height; ++y1)
					dst[x1 + y1 * width] = src[x + x1 + (y + y1) * wid];
		}
	}
	animationPool.insert({ name, {images,num } });
}

IMAGE* ResourceManager::Fetch(std::string name)
{
	return imagePool[name];
}

AnimationResource ResourceManager::FetchAnimation(std::string name)
{
	return animationPool[name];
}

