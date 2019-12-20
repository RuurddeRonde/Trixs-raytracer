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
		ImGuiUIManager(Window* window);
		~ImGuiUIManager();
		void update() override;
		void render() override;
	private:
		void initWindows(Window* window) override;
		UIWindow* startup;
		UIWindow* viewPort;
		UIWindow* renderSettings;
		UIWindow* showImage;
		IGRenderWindow* renderWindowCasted;
		IGShowImageWindow* showImageCasted;

		ImGuiWindowFlags window_flags;
		void ShowDockSpace(bool* p_open);
		void setstyle();
		void updateWindows();
		void deleteWindows();
	};
}