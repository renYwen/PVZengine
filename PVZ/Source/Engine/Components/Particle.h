#pragma once
#include"CoreMinimal.h"
#include"Tools/VisualInterface.h"
#include<chrono>
#include<queue>

using std::chrono::duration;
using std::chrono::steady_clock;
using std::chrono::time_point;


enum class ParticlePattern :uint8
{
	Center,/* 中心放射状 */
	Line/* 线性放射状 */
};

//单个粒子信息
struct ParticleInfo
{
	Vector2D offset;//相对于粒子创建器中心位置
	int index = 0; //当前帧索引
	Vector2D velocity; //速度
	time_point<steady_clock>lastTime;//粒子创建时间
	float alpha = 255.f; //透明度
	ParticleInfo() { lastTime = steady_clock::now(); }
};



//粒子组件
class Particle final : public SceneComponent, public LayerInterface, public ImageInterface
{
	std::deque<ParticleInfo>particles;
	int capacity = 0; //粒子容量

	float speed = 1.f; //粒子速度
	float graivity = 9.8f; //重力加速度

	float lifeCycle = 1.f; //粒子生命周期
	bool isLoop = true; //是否循环生产
	time_point<steady_clock>lastTime;//用于记录生产
	float interval = 0.1f; //生产间隔
	float fadingTime = 0; //粒子逐渐消失的时间

	IMAGE** images = nullptr;//粒子帧数组
	int number = 0; //粒子帧数
	

	ParticlePattern pattern = ParticlePattern::Center; //粒子放射状模式
	Vector2D unitVector = Vector2D(0, 1); //粒子方向单位向量
	/* 中心放射状属性成员 */
	Vector2D radius = Vector2D(0, 0);//内外径
	Vector2D scoop = Vector2D(0, 360);//放射范围
	/* 线性放射状属性成员 */
	float length = 1.f; //线性放射长度
	float angle = 0.f; //线性放射角度

	void Produce(); //产生粒子
public:
	Particle() {lastTime = steady_clock::now();}
	void Load(std::string name);

	virtual void Update()override;
	virtual void Render()override;

	/* 设置粒子容量 */
	void SetCapacity(int capacity) { this->capacity = capacity; }
	/* 设置粒子发射初速度 */
	void SetSpeed(float speed) { this->speed = speed; }
	/* 设置粒子重力 */
	void SetGraivity(float graivity) { this->graivity = graivity; }
	/* 设置单个粒子生命周期 */
	void SetLifeCycle(float lifeCycle) { this->lifeCycle = lifeCycle; }
	/* 设置粒子是否持续生产 */
	void SetIsLoop(bool isLoop) { this->isLoop = isLoop; }
	/* 设置粒子生产间隔 */
	void SetInterval(float interval) { this->interval = interval; }
	/* 设置粒子渐变消失时间 */
	void SetFadingTime(float fadingTime) { this->fadingTime = fadingTime; }

	/* 设置粒子模式 */
	void SetPattern(ParticlePattern pattern) { this->pattern = pattern; }
	/* 设置中心放射状参数 */
	void SetCenter(Vector2D radius, Vector2D scoop = Vector2D(0, 360)) { this->radius = radius; this->scoop = scoop; }
	/* 设置线性放射状参数 */
	void SetLine(float length, float angle) { this->length = length; this->angle = angle; }
};




