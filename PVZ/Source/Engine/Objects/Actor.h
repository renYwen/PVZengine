#pragma once
#include"CoreMinimal.h"


class ActorComponent;
class SceneComponent;


/* 场景对象基类 */
class Actor :public Object
{
	friend class RigidBody;

	std::unordered_set<Actor*>children;
	Actor* parent = nullptr;//处理场景属性关系 并且 便于增删

	std::unordered_set<ActorComponent*>components;
	std::unordered_set<ActorComponent*>::iterator components_iter;//管理组件的遍历以及增删

protected:
	SceneComponent* const root = nullptr;//场景根组件，赋予场景属性
public:
	Actor();

	virtual ~Actor() = 0;

	virtual void Update()override;

	virtual void BeginPlay()override;

	virtual void EndPlay()override;

	//设置场景根组件
	void SetRootComponent(SceneComponent* newRoot);

	//设置所属对象
	void AttachTo(Actor* par);

	//解除所属对象
	void DetachFrom(Actor* par);


	//将组件注册到对象容器
	void RegisterComponent(ActorComponent* pCom);

	//从对象容器中注销组件
	void UnregisterComponent(ActorComponent* pCom);

	//销毁游戏对象
	void Destroy();

	//获取场景属性（相对父对象坐标系）
	const Vector2D& GetLocalPosition() const;
	float GetLocalRotation() const;
	const Vector2D& GetLocalScale() const;

	//获取场景属性（世界绝对坐标系）
	Vector2D GetWorldPosition()const;
	float GetWorldRotation()const;
	Vector2D GetWorldScale()const;

	//设置场景属性（相对父对象坐标系）
	void SetLocalPosition(const Vector2D& pos);
	void SetLocalRotation(float angle);
	void SetLocalScale(const Vector2D& scale);

	//增加场景属性偏移量
	void AddPosition(Vector2D pos);
	void AddRotation(float rot);

	//绘制位置信息
	void DrawDebugPosition() const;

	//创建组件,绑定到对象,并注册到对象容器
	template<typename T>
	T* ConstructComponent()
	{
		T* pCom = new T;
		if (pCom && static_cast<ActorComponent*>(pCom))
		{
			pCom->SetOwner(this);
			RegisterComponent(pCom);
			return pCom;
		}
		delete pCom;
		return nullptr;
	}

	//通过类名获取组件
	template<typename T>
	T* GetComponentByClass()
	{
		for (auto& com : components)
		{
			if (T* pCom = dynamic_cast<T*>(com))return pCom;
		}
		return nullptr;
	}
};

