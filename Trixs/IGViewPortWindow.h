#pragma once
#include "ImGuiWindow.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "RenderManager.h"

namespace Trixs
{
	class IGViewPortWindow : public ImGuiWindow
	{
	public:
		IGViewPortWindow() {}
		void update() override;
		void setRenderManager(RenderManager* renderman) { this->renderman = renderman; }
	private:
		RenderManager* renderman;
	};

	void IGViewPortWindow::update()
	{
		if (show)
		{
			if (!begin("Viewport"))
			{
				end();
			}
			else
			{
				auto tex = renderman->getFrame();
				ImVec2 pos = ImGui::GetCursorScreenPos();
				ImGui::GetWindowDrawList()->AddImage((void *)tex, ImVec2(ImGui::GetCursorScreenPos()),
					ImVec2(ImGui::GetCursorScreenPos().x + SCR_WIDTH / 2, ImGui::GetCursorScreenPos().y + SCR_HEIGHT / 2), ImVec2(0, 1), ImVec2(1, 0));
				end();
			}
		}

	}
}