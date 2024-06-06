#pragma once
#include<iostream>
#include<string>



/* ���������� */
class Object
{
	static int tag;
protected:
	std::string name;
public:
	Object() { tag++; name = typeid(this).name() + std::string(" ") + std::to_string(tag); }
	virtual ~Object() { tag--; }

	//��ȡ��ǩ��
	std::string GetName()const { return name; }
	//���ñ�ǩ��
	void SetName(const std::string& name) { this->name = name; }
	virtual void Update() = 0;
	virtual void BeginPlay() = 0;
};


/* ��Ϸ�ؿ� */
class Level :public Object
{
	friend class World;
	friend class GameplayStatics;

protected:
	class Controller* mainController = nullptr;

public:
	/* ��ذѹؿ���ʼ���߼�д��BeginPlay����ֹд�빹�캯�� */
	virtual void BeginPlay() {}
};


/* ȫ����Ϸ���� */
class GameInstance
{

};