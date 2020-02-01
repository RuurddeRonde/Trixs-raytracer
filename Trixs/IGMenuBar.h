#pragma once
#include "ImGuiWindow.h"
#include "IGFileDialog.h"
#include "MainManager.h"
#include "ModelLoader.h"
#include "Lambertian.h"
namespace Trixs
{

	class IGMenuBar : public ImGuiWindow
	{
	public:
		void update() override
		{
			if (show)
			{
				if (!begin("sceneObjects"))
				{
					end();
				}
				else
				{
					static imgui_ext::file_browser_modal fileBrowser("Import");

					// Had to use this awkward approach to get the menu item to open the pop-up modal.
					bool isImportClicked = false;
					if (ImGui::BeginMainMenuBar()) {
						if (ImGui::BeginMenu("File"))
						{
							if (ImGui::MenuItem("Open Project")) {
								//isImportClicked = true;
							}
							if (ImGui::MenuItem("New Project")) {
								//isImportClicked = true;
							}
							if (ImGui::MenuItem("Save Project")) {
								//isImportClicked = true;
							}
							if (ImGui::MenuItem("Save and Quit")) {
								//isImportClicked = true;
							}
							if (ImGui::MenuItem("Quit")) {
								//isImportClicked = true;
							}
							ImGui::EndMenu();
						}
						
						if (ImGui::BeginMenu("Models")) {
							if (ImGui::MenuItem("Import")) {
								isImportClicked = true;
							}
							ImGui::EndMenu();
						}
						ImGui::EndMainMenuBar();
					}


					std::string path;
					if (fileBrowser.render(isImportClicked, path)) {
						isImportClicked = false;
						MainManager::getInstance().getProject()->getCurrentScene()->submit(ModelLoader::LoadMesh(path, new Lambertian(vec3(0.4, 0.2, 0.1))));
					}
					end();
				}
			}
		}
	private:
		bool keepscale;
	};

}