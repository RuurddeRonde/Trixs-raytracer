#pragma once
#include "UIWindow.h"
namespace Trixs
{
	class ImGuiWindow :
		public UIWindow
	{
	public:
		ImGuiWindow();
		~ImGuiWindow();
		void update() override;
	};

}