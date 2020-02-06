#include "IGStartupWindow.h"
#include "IGFileDialog.h"
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
				if (!newprojectPressed)
				{
					showStart();
				}
				else
				{
					showNew();
				}

				end();
			}
		}
	}

	void IGStartupWindow::showStart()
	{
		static imgui_ext::file_browser_modal fileBrowser("Load Project");
		bool isImportClicked = false;
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
			newprojectPressed = true;
		}
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::Button("  Load project  "))
		{
			isImportClicked = true;
		}
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::Button("      Quit      "))
		{
			exit(0);
		}

		std::string path;
		if (fileBrowser.render(isImportClicked, path))
		{
			isImportClicked = false;
			MainManager::getInstance().getProgramSettings()->newProjectName = path;	
			MainManager::getInstance().getProgramSettings()->loadProjectFromDisk = true;
			MainManager::getInstance().getProgramSettings()->projectAdjusted = true;
		}

	}
	void IGStartupWindow::showNew()
	{
		ImGui::Indent();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Text("Create new Project");
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		static char str0[128] = "new project name...";
		ImGui::Text("Name:");
		ImGui::InputText("##projectname", str0, IM_ARRAYSIZE(str0));
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		if (ImGui::Button("cancel"))
		{
			newprojectPressed = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Create"))
		{
			MainManager::getInstance().getProgramSettings()->newProject = true;
			MainManager::getInstance().getProgramSettings()->newProjectName = str0;
			MainManager::getInstance().getProgramSettings()->projectAdjusted = true;
			show = false;
		}
	}
}