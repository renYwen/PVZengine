#pragma once
#include <random>



/* ��ѧ���� */
class Math
{
	static std::random_device rd;
	static std::mt19937 gen;
public:
	//��ȡ�������������
	static int RandInt(int lower,int upper);
	//��ȡʵ�����������
	static double RandReal(double lower,double upper);
	//��ȡ0-1֮��������
	static double RandPerc();

	//��ĳ��������ĳ����Χ��
	template<typename T>
	static T Clamp(T value, T lower, T upper)
	{
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
		return MIN(MAX(value, MIN(lower, upper)), MAX(lower, upper));
	}
};



