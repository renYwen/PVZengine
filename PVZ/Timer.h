#pragma once
#include<functional>
#include<chrono>

using std::chrono::duration;
using std::chrono::steady_clock;
using std::chrono::time_point;

//¼ÆÊ±Æ÷
class Timer final
{
public:
	Timer() { lastTime = steady_clock::now(); }
	~Timer() { mainWorld.GameTimers.erase(this); }


	template<typename T>
	void Bind(double del,T*obj, void(T::*func)(),bool repeat = false)
	{
		callback = std::bind(func, obj); 
	    delay = duration<double>(del);
		lastTime = steady_clock::now();
		bPersistent = repeat;
		mainWorld.GameTimers.insert(this);
	}

	void Bind(double del, std::function<void()>func, bool repeat = false)
	{
		callback = func;
		delay = duration<double>(del); std::chrono::duration<int>(10);
		lastTime = steady_clock::now();
		bPersistent = repeat;
		mainWorld.GameTimers.insert(this);
	}

	void Execute()
	{
		if (delay.count() > 0 && getDelay().count() >= delay.count() && bRunning)
		{
			callback();
			if (bPersistent)lastTime = steady_clock::now();
			else delay = duration<double>(0);
		}
	}

	double GetDelay() { return getDelay().count(); }

	void SetDelay(double time) { delay = duration<double>(time); }

	void Reset() { lastTime = steady_clock::now(); }

	void Stop() { bRunning = false; }

	void Continue() { bRunning = true; }

private:
	std::function<void()> callback;
	bool bPersistent = false;
	bool bRunning = true;

	duration<double>delay = duration<double>(0);
	time_point<steady_clock>lastTime;


	duration<double> getDelay()
	{
		return steady_clock::now() - lastTime;
	}

};

