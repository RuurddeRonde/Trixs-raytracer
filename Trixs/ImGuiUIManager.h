#pragma once
#include "UIManager.h"
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

		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
	};

}