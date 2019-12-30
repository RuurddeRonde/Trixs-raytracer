#include "IGStartupWindow.h"
namespace Trixs
{
	bool IGStartupWindow::begin(std::string name)
	{
		ImGuiWindowFlags window_flags = 0;
		//window_flags |= ImGuiWindowFlags_NoSavedSettings;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoDocking;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		return ImGui::Begin(name.c_str(), &show, window_flags);
	}
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
				ImGui::Indent();
				ImGui::Spacing();
				ImGui::Spacing();
				ImGui::Text("Welcome to Trixs!");
				ImGui::Spacing();
				ImGui::Spacing();
				if (ImGui::Button("Continue project"))
				{
					MainManager::getInstance().getProgramSettings()->loadPreviousProject = true;
					MainManager::getInstance().getProgramSettings()->projectAdjusted = true;
					show = false;
				}
				ImGui::Spacing();
				ImGui::Spacing();
				if (ImGui::Button("   New project  "))
				{
					//start new project
					//MainManager::SetNewProject(std::string(str0));
					//show = false;
				}
				ImGui::Spacing();
				ImGui::Spacing();
				if (ImGui::Button("  Load project  "))
				{
					//show = false;
				}
				ImGui::Spacing();
				ImGui::Spacing();
				if (ImGui::Button("      Quit      "))
				{
					exit(0);
				}
				
				end();
			}
		}

	}
}