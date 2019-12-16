#pragma once
#include "UIManager.h"
#include "UIWindow.h"
#include "RenderManager.h"
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
		void initWindows(RenderManager* renderman) override;
	private:
		UIWindow* startup;
		UIWindow* viewPort;
		UIWindow* renderSettings;

		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
		void setstyle();
		void updateWindows();
		void deleteWindows();
	};
}