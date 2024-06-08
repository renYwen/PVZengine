#pragma once
#include "ActorComponent.h"
#include <unordered_map>
#include <functional>


enum class InputType :uint8
{
	Pressed,
	Released,
	Holding
};

enum KeyCode :int32
{
	VK_LButton = 1,
	VK_RButton,
	VK_MButton = 4,
	VK_A = 0x41,
	VK_B,VK_C,VK_D,
	VK_E,VK_F,VK_G,
	VK_H,VK_I,VK_J,
	VK_K,VK_L,VK_M,
	VK_N,VK_O,VK_P,
	VK_Q,VK_R,VK_S,
	VK_T,VK_U,VK_V,
	VK_W,VK_X,VK_Y,
	VK_Z,
};


struct KeyBindInfo
{
	std::function<void()> func;
	InputType type = InputType::Pressed;
	bool isPressed = false;
};

//输入交互组件
class InputComponent final: public ActorComponent
{
public:
	virtual void Update() override;

	//设置按键映射
	void SetMapping(std::string mappingName, KeyCode value);

	//绑定按键映射
	template<typename T>
	void BindAction(std::string actionName,InputType type, T* obj, void(T::*func)())
	{
	    if(mappings.find(actionName)!= mappings.end())
		callbacks.insert({ actionName, { std::bind(func, obj),type,false } });
	}

	//绑定按键映射
	void BindAction(std::string actionName, InputType type, std::function<void()>func);

	//获取鼠标屏幕坐标
	static Vector2D GetMousePosition();
	
	//鼠标左键是否按下
	static bool IsMouseButtonPressed();

	//激活输入输出
	static void EnableInput(bool enable);
private:
	std::unordered_map<std::string, KeyCode>mappings;
	std::unordered_map<std::string, KeyBindInfo>callbacks;
	static Vector2D mousePos;
	static bool bActive;
};
