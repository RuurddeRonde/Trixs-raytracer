#pragma once
#include "ImGuiWindow.h"
#include "MainManager.h"
namespace Trixs
{

	//window for creating or switching scenes
	class IGNewSceneWindow : public ImGuiWindow
	{
	public:
		void update() override
		{
			if (show)
			{
				if (!begin("NewScene"))
				{
					end();
				}
				else
				{
					for (auto i = 0; i < MainManager::getInstance().getProject()->getAllScenes().size(); i++)
					{
						//show all scenes in project
						if (i % 2 != 0)
						{
							ImGui::SameLine(); //two on a row
						}
						if (ImGui::Button(MainManager::getInstance().getProject()->getAllScenes().at(i)->getName().c_str(), ImVec2(ImGui::GetWindowWidth()/2, ImGui::GetWindowWidth() / 2 * 0.9)))
						{
							MainManager::getInstance().getProject()->switchScene(i);
							show = false;
							end();
							return;
						}
					}
					static char newSceneName[128] = "NewSceneName";
					ImGui::InputText("###NSN", newSceneName, IM_ARRAYSIZE(newSceneName), ImGuiInputTextFlags_CharsNoBlank);
					ImGui::SameLine();
					if (ImGui::Button("Create"))
					{
						//add new scene to current project
						MainManager::getInstance().getProject()->createNewScene(newSceneName);
						MainManager::getInstance().getProject()->switchScene(newSceneName);
					}
					end();
				}
			}
		}
	private:
	};

}