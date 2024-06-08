#pragma once
#include"Widgets.h"




/* UI¿‡ */
class UserInterface : public Object
{
	friend Panel;
	std::unordered_set<Widget*>widgets;

	void BeginPlay()override {}

protected:
	Widget* const rootCanvas = new Widget;
public:
	UserInterface();
	~UserInterface() { for (auto& widget : widgets)delete widget; }

	virtual void Update();

	void ShowInfoBoxs();

	template<class T>
	T* AddWidget()
	{
		T* gameWid = new T;
		if (Widget* buf = static_cast<Widget*>(gameWid))
		{
			widgets.insert(buf);
			return gameWid;
		}
		delete gameWid;
		return nullptr;
	}

	
	void AddToViewport();

	void HideFromViewport();

	void RemoveFromViewport();
};