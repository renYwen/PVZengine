#pragma once
#include"Widgets.h"




/* UI¿‡ */
class UserInterface : public Object
{
	friend Panel;
	std::unordered_set<Widget*>widgets;
protected:
	Widget* const rootCanvas = new Widget;
public:
	UserInterface() { rootCanvas->SetSize({ WIN_WIDTH,WIN_HEIGHT }); }
	~UserInterface() { for (auto& widget : widgets)delete widget; }

	virtual void Update();

	virtual void BeginPlay() { ; }

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