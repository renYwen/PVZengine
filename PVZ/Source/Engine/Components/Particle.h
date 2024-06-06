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
	Center,/* ���ķ���״ */
	Line/* ���Է���״ */
};

//����������Ϣ
struct ParticleInfo
{
	Vector2D offset;//��������Ӵ���������λ��
	int index = 0; //��ǰ֡����
	Vector2D velocity; //�ٶ�
	time_point<steady_clock>lastTime;//���Ӵ���ʱ��
	float alpha = 255.f; //͸����
	ParticleInfo() { lastTime = steady_clock::now(); }
};



//�������
class Particle final : public SceneComponent, public LayerInterface, public ImageInterface
{
	std::deque<ParticleInfo>particles;
	int capacity = 0; //��������

	float speed = 1.f; //�����ٶ�
	float graivity = 9.8f; //�������ٶ�

	float lifeCycle = 1.f; //������������
	bool isLoop = true; //�Ƿ�ѭ������
	time_point<steady_clock>lastTime;//���ڼ�¼����
	float interval = 0.1f; //�������
	float fadingTime = 0; //��������ʧ��ʱ��

	IMAGE** images = nullptr;//����֡����
	int number = 0; //����֡��
	

	ParticlePattern pattern = ParticlePattern::Center; //���ӷ���״ģʽ
	Vector2D unitVector = Vector2D(0, 1); //���ӷ���λ����
	/* ���ķ���״���Գ�Ա */
	Vector2D radius = Vector2D(0, 0);//���⾶
	Vector2D scoop = Vector2D(0, 360);//���䷶Χ
	/* ���Է���״���Գ�Ա */
	float length = 1.f; //���Է��䳤��
	float angle = 0.f; //���Է���Ƕ�

	void Produce(); //��������
public:
	Particle() {lastTime = steady_clock::now();}
	void Load(std::string name);

	virtual void Update()override;
	virtual void Render()override;

	/* ������������ */
	void SetCapacity(int capacity) { this->capacity = capacity; }
	/* �������ӷ�����ٶ� */
	void SetSpeed(float speed) { this->speed = speed; }
	/* ������������ */
	void SetGraivity(float graivity) { this->graivity = graivity; }
	/* ���õ��������������� */
	void SetLifeCycle(float lifeCycle) { this->lifeCycle = lifeCycle; }
	/* ���������Ƿ�������� */
	void SetIsLoop(bool isLoop) { this->isLoop = isLoop; }
	/* ��������������� */
	void SetInterval(float interval) { this->interval = interval; }
	/* �������ӽ�����ʧʱ�� */
	void SetFadingTime(float fadingTime) { this->fadingTime = fadingTime; }

	/* ��������ģʽ */
	void SetPattern(ParticlePattern pattern) { this->pattern = pattern; }
	/* �������ķ���״���� */
	void SetCenter(Vector2D radius, Vector2D scoop = Vector2D(0, 360)) { this->radius = radius; this->scoop = scoop; }
	/* �������Է���״���� */
	void SetLine(float length, float angle) { this->length = length; this->angle = angle; }
};




