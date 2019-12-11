#pragma once
namespace Trixs
{
	class UIWindow
	{
	public:
		UIWindow();
		~UIWindow();
		virtual void update() = 0;
	};

}