#include "ImGuiWindow.h"


namespace Trixs
{
	ImGuiWindow::ImGuiWindow()
	{
	}

	void ImGuiWindow::update()
	{
		begin("Base window");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		end();
	}

	ImGuiWindow::~ImGuiWindow()
	{
	}

	bool ImGuiWindow::begin(std::string name)
	{
		return ImGui::Begin(name.c_str(), &show);
	}
	void ImGuiWindow::end()
	{
		ImGui::End();
	}
}