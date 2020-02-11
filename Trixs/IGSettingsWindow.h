#pragma once
#include "ImGuiWindow.h"
#include "MainManager.h"
namespace Trixs
{

	class IGSettingsWindow : public ImGuiWindow
	{
	public:
		void update() override
		{
			if (show)
			{
				if (!begin("Settings"))
				{
					end();
				}
				else
				{
					ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
					ImGui::Text("Settings");
					ImGui::Separator();
					if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
					{
						if (ImGui::BeginTabItem("Standard settings"))
						{
							ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
							ImGui::EndTabItem();
						}
						if (ImGui::BeginTabItem("Render settings"))
						{
							ImGui::ColorPicker3("Background color", MainManager::getInstance().getProgramSettings()->backgroundColor.e);
							ImGui::EndTabItem();
						}
						ImGui::EndTabBar();
					}
					ImGui::EndChild();

					end();
				}
			}
		}
	private:
	};

}