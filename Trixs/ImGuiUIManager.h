#pragma once
#include "UIManager.h"
#include "UIWindow.h"
#include <vector>
#include <memory>
#include "RenderWindow.h"
#include "IGShowImageWindow.h"
namespace Trixs
{
	class ImGuiUIManager :
		public UIManager
	{
	public:
		ImGuiUIManager(){}
		ImGuiUIManager(Window* window);
		~ImGuiUIManager();
		void update() override;
		void render() override;
	private:
		void initWindows(Window* window) override;
		std::vector<ImGuiWindow> windows;
		UIWindow* startup;
		UIWindow* viewPort;
		UIWindow* renderSettings;
		UIWindow* showImage;
		UIWindow* SceneObjects;
		UIWindow* TimeLine;
		UIWindow* MenuBar;
		UIWindow* Settings;
		UIWindow* SceneManagement;
		IGRenderWindow* renderWindowCasted;
		IGShowImageWindow* showImageCasted;

		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
		void setstyle();
		void updateWindows();
		void deleteWindows();
	};
}