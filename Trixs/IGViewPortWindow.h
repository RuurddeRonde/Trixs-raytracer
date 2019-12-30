#pragma once
#include "ImGuiWindow.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Window.h"
#include "RenderManager.h"

namespace Trixs
{
	class IGViewPortWindow : public ImGuiWindow
	{
	public:
		IGViewPortWindow(Window* window)
		{
			this->window = window;
			this->renderman = new RenderManager(window);
		}
		void update() override;
		bool begin(std::string name) override;
		void setRenderManager(RenderManager* renderman) { this->renderman = renderman; }
	private:
		Window* window;
		RenderManager* renderman;
		ImVec2 size;
	};

	void IGViewPortWindow::update()
	{
		if (renderman->WindowShouldClose())
		{
			MainManager::getInstance().stop();
			return; //stop application
		}
		if (show)
		{
			struct CustomConstraints // Helper functions
			{
				static void Square(ImGuiSizeCallbackData* data) { data->DesiredSize.x = data->DesiredSize.y = (data->DesiredSize.x > data->DesiredSize.y ? data->DesiredSize.x : data->DesiredSize.y); }
			};

			ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);
			
			if (!begin("Viewport"))
			{
				end();
			}
			else
			{
				renderman->setNewSize(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
				renderman->render();
				auto tex = renderman->getFrame();

				size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
				ImGui::Image((void *)tex, size);
				end();
			}
		}

	}
	inline bool IGViewPortWindow::begin(std::string name)
	{
		return ImGui::Begin(name.c_str(), &show, ImGuiWindowFlags_NoScrollbar);
	}
}