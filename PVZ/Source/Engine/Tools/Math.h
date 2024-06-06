#pragma once
#include <random>



/* 数学工具 */
class Math
{
	static std::random_device rd;
	static std::mt19937 gen;
public:
	//获取整数类型随机数
	static int RandInt(int lower,int upper);
	//获取实数类型随机数
	static double RandReal(double lower,double upper);
	//获取0-1之间的随机数
	static double RandPerc();

	//将某数限制在某个范围内
	template<typename T>
	static T Clamp(T value, T lower, T upper)
	{
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
		return MIN(MAX(value, MIN(lower, upper)), MAX(lower, upper));
	}
};



