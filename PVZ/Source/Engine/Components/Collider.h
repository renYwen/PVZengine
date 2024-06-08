#pragma once
#include"SceneComponent.h"
#include"Tools/Delegate.h"
#include"Tools/CollisionManager.h"
#include"Core/World.h"


/* ��ײ����״ */
enum class ColliderShape:uint8 { Circle, Box };

/* ��ײ��ģʽ */
enum class CollisionMode:uint8 { None, Trigger, Collision };


class RigidBody;
class Controller;
class Collider;


//��ײ���
struct HitResult
{
	Vector2D ImpactPoint;
	Vector2D ImpactNormal;
	Actor* HitObject;
	ActorComponent* HitComponent;

	HitResult() :ImpactPoint(0, 0), ImpactNormal(0, 0), HitObject(nullptr), HitComponent(nullptr) {}
	HitResult(const Vector2D& impactPoint, const Vector2D& impactNormal, Actor* hitObject, ActorComponent* hitComponent)
		:ImpactPoint(impactPoint), ImpactNormal(impactNormal), HitObject(hitObject), HitComponent(hitComponent) {}
};




//��ײί��

/* Collider* overlapComp, Collider* otherComp, Actor* otherActor */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionOverlapDelegate, Collider*,Collider*, Actor*)

/* Collider* hitComp, Collider* otherComp, Actor* otherActor, Vector2D normalImpulse, const HitResult& hitResult */
DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(CollisionHitDelegate, Collider* ,Collider*, Actor*, Vector2D, const HitResult&)






/* ��ײ�� */
class Collider :public SceneComponent
{
	DEFINE_SUPER(SceneComponent)

	friend Controller;
	friend RigidBody;
	friend void World::ProcessColliders();

public:
	Collider():type(CollisionType::Default) { mainWorld.GameColliders.insert(this); }
	virtual ~Collider();

	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void Deactivate()override;

	//��ȡ���ں͸���ײ�巢����ײ��ĳһָ����ײ���͵�������ײ��ָ�룬��������ʽ����
	const std::vector<Actor*>& GetCollisions(CollisionType type);

	//��ײ�㼶
	int GetLayer()const { return layer; }
	void SetLayer(int layer) { this->layer = layer; }

	//��ײ����
	CollisionType GetType()const { return type; }
	void SetType(CollisionType type) { this->type = type; }

	//��ײ����״
	ColliderShape GetShape()const { return shape; }

	//��ײģʽ
	void SetCollisonMode(CollisionMode mode);
	CollisionMode GetCollisonMode()const { return mode; }

	//���Ƶ�����
	virtual void DrawDebugLine() = 0;

	//��ײ�¼�
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
	std::vector<Actor*>aims;
	std::vector<Collider*>collisions_to_erase;

  
	void Clear();
	void Insert(Collider* another);
	void Erase();


	bool CollisionJudge(Collider* another);

	//��ײ�ж�
	static bool (*collisionJudgeMap[3])(Collider*, Collider*);
	static bool collisionJudgeCircleToCircle(Collider* c1, Collider* c2);
	static bool collisionJudgeCircleToBox(Collider* c1, Collider* c2);
	static bool collisionJudgeBoxToBox(Collider* c1, Collider* c2);
	
	HitResult CollisionHit(Collider* another);

	//��ײ��Ϣ
	static HitResult (*collisionHitMap[3])(Collider*, Collider*);
	static HitResult collisionHitCircleToCircle(Collider* c1, Collider* c2);
	static HitResult collisionHitCircleToBox(Collider* c1, Collider* c2);
	static HitResult collisionHitBoxToBox(Collider* c1, Collider* c2);


	RigidBody* rigidAttached = nullptr;//���ŵĸ���
};



/* Բ����ײ�� */
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



/* ������ײ�� */
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

	//��ȡ�ص����ο�ߣ��贫���Ѿ�ȷ��������ײ��������ײ��
	static Vector2D GetOverlapRect(const Rect& r1, const Rect& r2);
private:
	Vector2D size = Vector2D(0, 0);
	Vector2D size_ini = Vector2D(0, 0);
	Rect rect;
};





