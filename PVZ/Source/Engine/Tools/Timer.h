#pragma once
#include"Core/World.h"
#include<functional>
#include<chrono>


using std::chrono::duration;
using std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::milliseconds;



//计时器
class Timer final
{
	friend class World;
public:
	Timer() { lastTime = steady_clock::now(); }
	~Timer() { mainWorld.GameTimers.erase(this); }

	//绑定计时器，默认情况下只执行一次，如果多次执行，可以指定首次执行时间间隔
	template<typename T>
	void Bind(double delay, T* obj, void(T::* function)(), bool repeat = false, double firstDelay = -1.0)
	{
		callback = std::bind(function, obj); 
	    this->delay = duration<double>(delay);
		lastTime = steady_clock::now();
		if (firstDelay>=0)lastTime -= milliseconds(int(1000 * (delay - firstDelay)));
		bPersistent = repeat;
		mainWorld.GameTimers.insert(this);
	}

	//绑定计时器，默认情况下只执行一次，如果多次执行，可以指定首次执行时间间隔
	void Bind(double delay, std::function<void()>function, bool repeat = false, double firstDelay = -1.0);

	//获取距离上一次执行的时间
	double GetDelay() { return getDelay().count(); }

	//设置执行间隔
	void SetDelay(double time) { delay = duration<double>(time); }

	//重置计时器
	void Reset() { lastTime = steady_clock::now(); }

	//暂停计时器
	void Stop() { bRunning = false; stopTime = steady_clock::now();}

	//启动计时器
	void Continue() { bRunning = true; lastTime += (steady_clock::now() - stopTime); }

private:
	std::function<void()> callback;
	bool bPersistent = false;
	bool bRunning = true;

	duration<double>delay = duration<double>(0);
	time_point<steady_clock>lastTime;
	time_point<steady_clock>stopTime;


	duration<double> getDelay()
	{
		return steady_clock::now() - lastTime;
	}

	void Execute();
};

