#pragma once
#include "UIManager.h"
#include "UIWindow.h"
#include <vector>
#include <memory>
namespace Trixs
{
	class ImGuiUIManager :
		public UIManager
	{
	public:
		ImGuiUIManager(GLFWwindow* window);
		~ImGuiUIManager();
		void update() override;
		void render() override;
	private:
		std::vector<UIWindow*> windows;

		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
		void initWindows();
		void setstyle();
	};

	///windows
	///[0] startup window
}