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
						if (ImGui::Button(MainManager::getInstance().getProject()->getAllScenes().at(i)->getName().c_str()))
						{
							MainManager::getInstance().getProject()->switchScene(i);
							show = false;
							end();
							return;
						}
					}
					static char newSceneName[128] = "New Scene Name";
					ImGui::InputText("###NSN", newSceneName, IM_ARRAYSIZE(newSceneName));
					ImGui::SameLine();
					if (ImGui::Button("Create"))
					{
						//add new scene to current project
						MainManager::getInstance().getProject()->createNewScene(newSceneName);
					}
					end();
				}
			}
		}
	private:
	};

}