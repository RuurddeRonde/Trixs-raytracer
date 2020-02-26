#include "RenderWindow.h"
#include "RenderSubmission.h"
#include <future>
#include <algorithm>
#include "MainManager.h"

namespace Trixs
{

	void IGRenderWindow::update()
	{
		if (show)
		{
			if (!begin("Render"))
			{
				end();
			}
			else
			{
				ImGui::BeginChild("data", ImVec2(350, 75), false);
				ImGui::DragInt("Width in pixels", &this->nx, 1.0, 10, 1080);
				ImGui::DragInt("Height in pixels", &this->ny, 1.0, 10, 720);
				ImGui::DragInt("Samples per pixel", &this->ns, 1.0, 0, 500);

				ImGui::EndChild();

				static char str0[128] = "Render1";
				ImGui::Text("Filetype:");
				ImGui::SameLine();
				ImGui::Combo("###Output", &filetype, "JPG\0PNG\0BPM\0TGA\0HDR\0");

				ImGui::Text("Name:    ");
				ImGui::SameLine();
				ImGui::InputText("###Name", str0, IM_ARRAYSIZE(str0));

				if (ImGui::Button("Render"))
				{
					RenderSubmission sub;
					sub.width = nx;
					sub.height = ny;
					sub.samplesPerPixel = ns;
					sub.outputfile = str0;
					sub.outputType = (FileTypes)filetype;
					sub.scene = MainManager::getInstance().getProject()->getCurrentScene();
					RT.render(&sub);
					newImage = true;
					if (sub.outputType == FileTypes::JPG)
					{
						LastRenderPath = "renders/" + sub.outputfile + ".jpg";
					}
				}
				end();
			}
		}
	}
}