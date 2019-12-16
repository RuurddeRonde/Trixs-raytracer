#pragma once
#include "ImGuiWindow.h"
#include "MainManager.h"
namespace Trixs
{

	class IGStartupWindow : public ImGuiWindow
	{
	public:
		void update() override;
	private:

	};

	void IGStartupWindow::update()
	{
		if (show)
		{
			if (!begin("Startup"))
			{
				end();
			}
			else
			{
				ImGui::BeginChild("left", ImVec2(150, 0), false);
				if (ImGui::Button("Open project"))
				{
					//open filedir to open project
					show = false;
				}
				ImGui::Text("Project name: ");
				ImGui::SameLine();
				static char str0[128] = "";
				ImGui::InputText("Project1", str0, IM_ARRAYSIZE(str0));
				if (ImGui::Button("New project"))
				{
					//start new project
					//MainManager::SetNewProject(std::string(str0));
					show = false;
				}
				ImGui::EndChild(); //left
				ImGui::SameLine();
				ImGui::BeginChild("News", ImVec2(0, 0), false);
				ImGui::Text("The latest news will be displayed here!");
				ImGui::EndChild();
				end();
			}
		}

	}
}