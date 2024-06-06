#include "InputComponent.h"
#include <windows.h>



void InputComponent::SetMapping(std::string mappingName, KeyCode value)
{
	mappings.insert({mappingName, value});
}


void InputComponent::Update()
{
	POINT point;
	GetCursorPos(&point);
	mousePos = Vector2D(float(point.x),float(point.y));

	for (auto& mapping : mappings)
	{
		KeyBindInfo& info = callbacks[mapping.first];

		if (GetAsyncKeyState((int)mapping.second) & 0x8000)
		{
			if (info.type == InputType::Pressed && !info.isPressed)info.func();
			if (info.type == InputType::Holding)info.func();
			info.isPressed = true;
		}
		else if (info.isPressed)
		{
			if(info.type == InputType::Pressed)info.isPressed = false;
			else if (info.type == InputType::Released) {info.func(); info.isPressed = false;}
		}
	}

}


Vector2D InputComponent::GetMousePosition()
{
	return mousePos;
}

bool InputComponent::IsMouseButtonPressed()
{
	return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
}

Vector2D InputComponent::mousePos = {};
