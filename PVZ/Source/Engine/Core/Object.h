#pragma once
#include<iostream>
#include<string>



/* 基础对象类 */
class Object
{
	static int tag;
protected:
	std::string name;
public:
	Object() { tag++; name = typeid(this).name() + std::string(" ") + std::to_string(tag); }
	virtual ~Object() { tag--; }

	//获取标签名
	std::string GetName()const { return name; }
	//设置标签名
	void SetName(const std::string& name) { this->name = name; }
	virtual void Update() = 0;
	virtual void BeginPlay() = 0;
};


/* 游戏关卡 */
class Level :public Object
{
	friend class World;
	friend class GameplayStatics;

protected:
	class Controller* mainController = nullptr;

public:
	/* 务必把关卡初始化逻辑写进BeginPlay，禁止写入构造函数 */
	virtual void BeginPlay() {}
};


/* 全局游戏单例 */
class GameInstance
{

};