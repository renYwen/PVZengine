

/***************************
 *    核心代码文件 
 *
 *    基础外部头文件，基础结构体，基础类，基础函数，基础全局变量
 *
 ***************************/


#pragma once

//外部头文件
#include<iostream>
#include<string>
#include<set>
#include<unordered_set>
#include<vector>
#include<cmath>



//宏定义以及标准命名
constexpr double PI = 3.1415926;
constexpr float DELTA_TIME = 0.01f;
constexpr int WIN_WIDTH = 800;
constexpr int WIN_HEIGHT = 600;

typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef long long int64;
typedef int int32;
typedef short int16;
typedef char int8;

#define DEFINE_SUPER(SuperClass) typedef SuperClass Super;


//二维向量
struct Vector2D
{
	float x,y;
	Vector2D():x(0),y(0) {}
	Vector2D(float a, float b) :x(a), y(b) {}

	//获取向量长度
	float Size() const
	{
		return sqrtf(x*x + y*y);
	}

	//获取单位向量
	Vector2D Normalize() const
	{
	    return Vector2D(x / Size(), y / Size());
	}

	//将向量转化为字符串
	std::string ToString() const
	{
		return "(" + std::to_string((int)x) + "," + std::to_string((int)y) + ")";
	}

	//向量点积
	static float DotProduct(const Vector2D& v1, const Vector2D& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	//向量叉积
	static Vector2D CrossProduct(const Vector2D& v1, const Vector2D& v2) 
	{
		return { v1.y * v2.x - v1.x * v2.y, v1.x * v2.y - v1.y * v2.x };
	}

	//获取两个坐标之间的距离
	static float Distance(const Vector2D& a, const Vector2D& b)
	{
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	//旋转某一向量，返回旋转后的向量（单位是角度）
	static Vector2D RotateVector(float angle, const Vector2D& another)
	{
		double radian = PI * angle / 180;
		float fsin = float(sin(radian));
		float fcos = float(cos(radian));
		return Vector2D(another.x * fcos - another.y * fsin, another.x * fsin + another.y * fcos);
	}

	// 将向量 u 投影到向量 v 所在的直线上
	static Vector2D ProjectVector(const Vector2D& u, const Vector2D& v) 
	{
		float scalar = DotProduct(u, v) / v.Size();  // 计算投影向量的缩放因子
		return v.Normalize() * scalar;  
	}


	Vector2D operator+(const Vector2D& another)const
	{
		return Vector2D(x+another.x,y+another.y);
	}
	Vector2D operator-(const Vector2D& another)const
	{
		return Vector2D(x - another.x, y - another.y);
	}
	Vector2D& operator+=(const Vector2D& another)
	{
		x += another.x; y += another.y;
		return *this;
	}
	Vector2D& operator-=(const Vector2D& another)
	{
		x -= another.x; y -= another.y;
		return *this;
	}


	bool operator==(const Vector2D& another) const
	{
		return x == another.x && y == another.y;
	}
	bool operator!=(const Vector2D& another) const 
	{
	    return x!= another.x || y != another.y;
	}
	Vector2D operator*(float scale) const
	{
		return Vector2D(x * scale, y * scale);
	}
	Vector2D& operator*=(float scale)
	{
		x *= scale; y *= scale;
		return *this;
	}
	Vector2D operator/(float scale) const
	{
		return Vector2D(x / scale, y / scale);
	}
	Vector2D& operator/=(float scale)
	{
		x /= scale; y /= scale;
		return *this;
	}
	Vector2D operator-() const
	{
		return Vector2D(-x, -y);
	}
	Vector2D operator*(const Vector2D& another) const
	{
		return Vector2D(x * another.x , y * another.y);
	}
	Vector2D operator/(const Vector2D& another) const
	{
		return Vector2D(x / another.x, y / another.y);
	}
};

inline std::ostream& operator<<(std::ostream& out, const Vector2D& vec)
{
	std::cout << "(" << vec.x << "," << vec.y << ")";
	return out;
}

inline Vector2D operator*(float scale,Vector2D vec)
{
	return Vector2D(vec.x * scale, vec.y * scale);
}

//数对
struct Pair
{
	int x, y;
	Pair() :x(0), y(0) {}
	Pair(int x, int y) :x(x), y(y) {}
	bool operator==(const Pair& another) const
	{
		return x == another.x && y == another.y;
	}
	bool operator!=(const Pair& another) const
	{
		return x != another.x || y != another.y;
	}
};


//基础类
class Base
{
	static int64 tag;
protected:
	std::string name;
public:
	Base() { tag++; name = typeid(this).name() + std::string(" ") + std::to_string(tag); }
	virtual ~Base() { tag--; }
	std::string GetName()const { return name; }
	void SetName(const std::string& name) { this->name = name; }
	virtual void Update() = 0;
	virtual void BeginPlay() = 0;
};



//组件基类
class Component : public Base
{
protected:
	class Object* pOwner = nullptr;//处理控制逻辑
public:
	virtual void Update() {}

	virtual void BeginPlay(){}

	//设置绑定对象
	void SetOwner(class Object* owner) { pOwner = owner; }

	virtual void Destruct();
};


//场景属性类
struct Transform
{
	Vector2D position;
	float rotation;
	Vector2D scale;

	Transform() :position(0, 0), rotation(0), scale(1, 1) {}
	Transform(const Vector2D& pos, float angle, const Vector2D& scale) 
		:position(pos), rotation(angle), scale(scale) {}

	Transform Indentity() const
	{
		return Transform(Vector2D(0, 0), 0, Vector2D(1, 1));
	}

};


//场景组件基类
class SceneComponent : public Component
{
	Transform transform_local;
	std::unordered_set<SceneComponent*>children;
	SceneComponent* parent = nullptr;//处理场景属性关系 并且 便于增删

	void process_Destruct();


public:
	virtual void Update() override {}

	//设置所属组件
	void AttachTo(SceneComponent* par);

	//解除所属组件
	void DetachFrom(SceneComponent* par);

	
	virtual void Destruct() override;


	const Vector2D& GetLocalPosition() const { return transform_local.position; }
	float GetLocalRotation() const { return transform_local.rotation; }
	const Vector2D& GetLocalScale() const { return transform_local.scale; }

	Vector2D GetWorldPosition() const;
	float GetWorldRotation() const;
	Vector2D GetWorldScale() const;

	void SetLocalPosition(const Vector2D& pos) { transform_local.position = pos; }
	void SetLocalRotation(float angle) { transform_local.rotation = angle; }
	void SetLocalScale(const Vector2D& scale) { transform_local.scale = scale; }

	void AddPosition(Vector2D pos) { transform_local.position += pos; }
	void AddRotation(float rot) { transform_local.rotation += rot; }
};



//游戏对象基类
class Object :public Base
{
	friend class RigidBody;
	std::unordered_set<Object*>children;
	Object* parent = nullptr;//处理场景属性关系 并且 便于增删

	std::unordered_set<Component*>components;
	std::unordered_set<Component*>::iterator components_iter;//管理组件的遍历以及增删
	
protected:
	SceneComponent * const root = new SceneComponent;//场景根组件，赋予场景属性
public:
	Object() {root->SetOwner(this); RegisterComponent(root);}

	virtual ~Object()
	{
		for (auto &com : components)delete com;
	}


	virtual void Update()override;

	virtual void BeginPlay()override;

	//设置场景根组件
	void SetRootComponent(SceneComponent*newRoot)
	{
		const_cast<SceneComponent*&>(root) = newRoot;
	}

	//设置所属对象
	void AttachTo(Object* par);

	//解除所属对象
	void DetachFrom(Object* par);


	//将组件注册到对象容器
	void RegisterComponent(Component* pCom)
	{
		components.insert(pCom);
	}

	//从对象容器中注销组件
	void UnregisterComponent(Component* pCom)
	{
		components_iter = components.erase(components.find(pCom));
	}

	//创建组件,绑定到对象,并注册到对象容器
	template<typename T>
	T* ConstructComponent()
	{
		T* pCom = new T;
		if (pCom && static_cast<Component*>(pCom)) 
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

	
	//从mainWorld里删除对象
	void Destroy();

	const Vector2D& GetLocalPosition() const{ return root->GetLocalPosition(); }
	float GetLocalRotation() const { return root->GetLocalRotation(); }
	const Vector2D& GetLocalScale() const { return root->GetLocalScale(); }

	Vector2D GetWorldPosition()const;
	float GetWorldRotation()const;
	Vector2D GetWorldScale()const;

	void SetLocalPosition(const Vector2D& pos) { root->SetLocalPosition(pos); }
	void SetLocalRotation(float angle) { root->SetLocalRotation(angle); }
	void SetLocalScale(const Vector2D& scale) { root->SetLocalScale(scale); }

	void AddPosition(Vector2D pos) { root->AddPosition(pos); }
	void AddRotation(float rot) { root->AddRotation(rot); }

	void DrawDebugPosition() const;
};




//全局游戏单例
class GameInstance
{

};


//游戏关卡
class Level :public Base
{
	class Controller* mainController = nullptr;
public:
	Level()
	{
	
	}

	virtual void BeginPlay() override
	{
		;
	}

	virtual void Update() override
	{
		;
	}
};


//渲染图层排序规则
struct LayerSort
{
	bool operator()(const class LayerInterface* a, const class LayerInterface* b) const;
};
//碰撞图层排序规则
struct ColliderSort
{
	bool operator()(const class Collider* a, const class Collider* b) const;
};


//游戏世界
class World final
{
	/* 友元声明 */
	friend class Engine;
	friend class GameStatics;
	friend class Timer;
	friend class LayerInterface;
	friend void Object::Destroy();
	friend void Object::DrawDebugPosition()const;
	friend class ImageInterface;
	friend class Camera;
	friend class SpriteRenderer;
	friend class Animation;
	friend class Particle;
	friend class Collider;
	friend class CircleCollider;
	friend class BoxCollider;
	friend class Controller;
	friend class UserInterface;
	friend class Widget;
	friend class Button;
	friend class Bar;

	/* 资源池 */
	class ResourceManager* resourcePool = nullptr;

	/* 碰撞管理器 */
	class CollisionManager* collisionManager = nullptr;

	/* 全局计时器 */
	class Timer *FPSClock = nullptr;
	
	
	/* 场景对象、UI、计时器容器 */
	std::unordered_set<Object*>GameObjects;
	std::vector<Object*>GameObjects_to_add;
	std::unordered_set<Object*>GameObjects_to_delete;
	std::unordered_set<class UserInterface*>GameUIs;
	std::unordered_set<class UserInterface*>GameUIs_to_delete;
	std::unordered_set<class Timer*>GameTimers;
	

	/*  渲染、碰撞计算、UI鼠标检测容器 */
	std::set<class LayerInterface*, LayerSort>GameRenderers;
	std::unordered_set<class Collider*>GameColliders;
	std::unordered_set<class Collider*>GameColliders_to_clear;
	std::set<class Collider*, ColliderSort>ColliderZones[8][6];
	std::set<class LayerInterface*, LayerSort>UIDetectZones[8][6];

	/* 游戏单例对象 */
	Level *currentLevel = nullptr;
	class Controller* mainController = nullptr;
	GameInstance *gameInstance = nullptr;

	class Camera* mainCamera = nullptr;

	/* 核心逻辑遍历 */
	void Update();//逻辑处理

	void Update_();//高精度计算

	void Render();//渲染

	void Input();//交互处理

	void ProcessColliders();//碰撞计算

	/* Debug模式 */
	void Debug();
};

extern World mainWorld;




//类型转换
template<typename T, typename F>
inline T * Cast(F * pBase)
{
	if(pBase)return dynamic_cast<T*>(pBase);
	std::cout << "Cast Error!" <<std::endl;
	return nullptr;
}
