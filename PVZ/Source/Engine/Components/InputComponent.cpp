#include "InputComponent.h"
#include <easyx.h>



void InputComponent::SetMapping(std::string mappingName, KeyCode value)
{
	mappings.insert({mappingName, value});
}


void InputComponent::BindAction(std::string actionName, InputType type, std::function<void()> func)
{
	if (mappings.find(actionName) != mappings.end())
		callbacks.insert({ actionName, { func,type,false } });
}

void InputComponent::Update()
{
	if (!bIsEnabled||!bActive)return;

	ExMessage msg;
	if (peekmessage(&msg))
	{
		mousePos = Vector2D(float(msg.x),float(msg.y));
	}

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
		    if (info.type == InputType::Released)info.func();
			info.isPressed = false;
		}
	}

}


Vector2D InputComponent::GetMousePosition()
{
	return bActive ? mousePos : Vector2D{};
}

bool InputComponent::IsMouseButtonPressed()
{
	return bActive ? (GetAsyncKeyState(VK_LBUTTON) & 0x8000) : false;
}

void InputComponent::EnableInput(bool enable)
{
	bActive = enable;
}

Vector2D InputComponent::mousePos = {};
bool InputComponent::bActive = false;
