#pragma once
#include"CoreMinimal.h"
#include"Delegate.h"
#include"CollisionManager.h"


/* 碰撞体形状 */
enum class ColliderShape:uint8 { Circle, Box };

/* 碰撞体模式 */
enum class CollisionMode:uint8 { None, Trigger, Collision };





//碰撞结果
struct HitResult
{
	Vector2D ImpactPoint;
	Vector2D ImpactNormal;
	Object* HitObject;
	Component* HitComponent;

	HitResult() :ImpactPoint(0, 0), ImpactNormal(0, 0), HitObject(nullptr), HitComponent(nullptr) {}
	HitResult(const Vector2D& impactPoint, const Vector2D& impactNormal, Object* hitObject, Component* hitComponent)
		:ImpactPoint(impactPoint), ImpactNormal(impactNormal), HitObject(hitObject), HitComponent(hitComponent) {}
};




//碰撞委托

/* Collider* overlapComp, Collider* otherComp, Object* otherActor */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionOverlapDelegate, Collider*,Collider*, Object*)

/* Collider* hitComp, Collider* otherComp, Object* otherActor, Vector2D normalImpulse, const HitResult& hitResult */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionHitDelegate, Collider* ,Collider*, Object*, Vector2D, const HitResult&)






//碰撞器
class Collider :public SceneComponent
{
	friend class Controller;
	friend class RigidBody;
	friend void World::ProcessColliders();
public:
	Collider():type(CollisionType::Default) { mainWorld.GameColliders.insert(this); }
	virtual ~Collider();

	virtual void Update() override;

	/* 获取正在和该碰撞体发生碰撞的某一指定碰撞类型的所有碰撞体指针，以数组形式返回 */
	const std::vector<Object*>& GetCollisions(CollisionType type);

	int GetLayer()const { return layer; }
	void SetLayer(int layer) { this->layer = layer; }

	CollisionType GetType()const { return type; }
	void SetType(CollisionType type) { this->type = type; }

	ColliderShape GetShape()const { return shape; }

	void SetCollisonMode(CollisionMode mode);
	CollisionMode GetCollisonMode()const { return mode; }

	/* 绘制调试线 */
	virtual void DrawDebugLine() = 0;

	/* 碰撞事件 */
	CollisionOverlapDelegate OnComponentBeginOverlap;
	CollisionOverlapDelegate OnComponentEndOverlap;
	CollisionHitDelegate OnComponentHit;

protected:
	ColliderShape shape = ColliderShape::Circle;
	virtual bool IsMouseOver() = 0;

private:
	int layer = 0;
	CollisionType type;
	CollisionMode mode = CollisionMode::Trigger;

	Pair point{ -1, -1 }, point_1{ -1, -1 };
	std::unordered_set<Collider*>collisions;
	std::vector<Object*>aims;
	std::vector<Collider*>collisions_to_erase;

  
	void Clear();
	void Insert(Collider* another);
	void Erase();


	bool CollisionJudge(Collider* another);

	/* 碰撞判断 */
	static bool (*collisionJudgeMap[3])(Collider*, Collider*);
	static bool collisionJudgeCircleToCircle(Collider* c1, Collider* c2);
	static bool collisionJudgeCircleToBox(Collider* c1, Collider* c2);
	static bool collisionJudgeBoxToBox(Collider* c1, Collider* c2);
	
	HitResult CollisionHit(Collider* another);

	/* 碰撞信息 */
	static HitResult (*collisionHitMap[3])(Collider*, Collider*);
	static HitResult collisionHitCircleToCircle(Collider* c1, Collider* c2);
	static HitResult collisionHitCircleToBox(Collider* c1, Collider* c2);
	static HitResult collisionHitBoxToBox(Collider* c1, Collider* c2);
};



//圆形碰撞器
class CircleCollider final:public Collider
{
public:
	CircleCollider() {shape = ColliderShape::Circle;}
	virtual void Update()override;
	virtual void DrawDebugLine()override;
	virtual bool IsMouseOver()override;
	float GetRadius()const { return radius; }
	void SetRadius(float r) { radius = r; radius_ini = r/sqrtf(GetWorldScale().x * GetWorldScale().y); }
private:
	float radius = 0;
	float radius_ini = 0;
};



//矩形碰撞器
class BoxCollider final:public Collider
{
public:
	struct Rect
	{
		float left = 0, top = 0, right = 0, bottom = 0;
	};

	BoxCollider() { shape = ColliderShape::Box; }
	virtual void Update()override;
	virtual void DrawDebugLine()override;
	virtual bool IsMouseOver()override;
	Vector2D GetSize()const { return size; }
	void SetSize(Vector2D size) { this->size = size; size_ini = size / GetWorldScale(); }
	
	Rect GetRect()const { return rect; }

	//需传入已经确定发生碰撞的两个碰撞器
	static Vector2D GetOverlapRect(const Rect& r1, const Rect& r2);
private:
	Vector2D size = Vector2D(0, 0);
	Vector2D size_ini = Vector2D(0, 0);
	Rect rect;
};





