#pragma once
#include <string>
namespace Trixs
{
	class UIWindow
	{
	public:
		UIWindow();
		~UIWindow();
		virtual void update() = 0;
		bool shouldShow() { return show; }
	protected:
		bool show;
	};

}