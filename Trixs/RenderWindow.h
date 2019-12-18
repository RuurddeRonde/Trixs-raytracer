#pragma once
#include "ImGuiWindow.h"
#include "RayTrixser.h"
#include "RenderSubmission.h"
#include <future>
#include <algorithm>
namespace Trixs
{

	class IGRenderWindow : public ImGuiWindow
	{
	public:
		void update() override;
	private:
		RayTrixser RT;
		int randomObjects = 500;
		int nx = 200;
		int ny = 100;
		int ns = 10;
};

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
				ImGui::BeginChild("data", ImVec2(350, 150), false);
				ImGui::DragInt("Balls", &this->randomObjects, 1.0, 0, 500);
				ImGui::DragInt("Width in pixels", &this->nx, 1.0, 10, 1080);
				ImGui::DragInt("Height in pixels", &this->ny, 1.0, 10, 720);
				ImGui::DragInt("Samples per pixel", &this->ns, 1.0, 0, 500);

				ImGui::EndChild(); //left
				
				static char str0[128] = "Render1.ppm";
				ImGui::InputText("Name", str0, IM_ARRAYSIZE(str0));
				if (ImGui::Button("Render"))
				{
					RenderSubmission sub;
					sub.width = nx;
					sub.height = ny;
					sub.samplesPerPixel = ns;
					sub.outputfile = str0;
					sub.scene = MainManager::getInstance().getProject()->getCurrentScene();
					RT.render(sub);
				}
				end();
			}
		}

	}
}