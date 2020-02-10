#include "IGSceneObjectListWindow.h"
#include "MainManager.h"
void Trixs::IGSceneObjectListWindow::update()
{
	if (show)
	{
		if (!begin("sceneObjects"))
		{
			end();
		}
		else
		{
			std::vector<Hittable*>* objects = MainManager::getInstance().getProject()->getCurrentScene()->getObjects();

			static int selected = 0;
			ImGui::BeginChild("Objects", ImVec2(ImGui::GetWindowWidth()-10, 250), false);

			if (ImGui::Selectable("camera", selected == -1))
				selected = -1;

			for (int i = 0; i < objects->size(); i++)
			{
				char label[128];
				sprintf_s(label, "Object %d", i);
				if (ImGui::Selectable(label, selected == i))
					selected = i;
			}
			ImGui::EndChild();

			ImGui::Separator();

			if (selected != -1)
			{
				Transform* t = objects->at(selected)->getTransform();
				ImGui::Text("Object %d", selected);
				ImGui::Text("Position");

				ImGui::Text("X ");
				ImGui::SameLine();
				ImGui::SliderFloat("X##valueXp", &t->getPosPtr()->e[0], -20.0, 20.0);
				ImGui::Text("Y ");
				ImGui::SameLine();
				ImGui::SliderFloat("Y##valueYp", &t->getPosPtr()->e[1], -20.0, 20.0);
				ImGui::Text("Z ");
				ImGui::SameLine();
				ImGui::SliderFloat("Z##valueZp", &t->getPosPtr()->e[2], -20.0, 20.0);

				ImGui::Text("Rotation");

				ImGui::Text("X ");
				ImGui::SameLine();
				ImGui::SliderFloat("X##valueXr", &t->getRotPtr()->e[0], 0.1, 365);
				ImGui::Text("Y ");
				ImGui::SameLine();
				ImGui::SliderFloat("Y##valueYr", &t->getRotPtr()->e[1], 0.1, 365);
				ImGui::Text("Z ");
				ImGui::SameLine();
				ImGui::SliderFloat("Z##valueZr", &t->getRotPtr()->e[2], 0.1, 365);

				ImGui::Text("Scale");
				ImGui::Checkbox("Keep scale equal", &keepscale);
				if (keepscale)
				{
					ImGui::Text("X ");
					ImGui::SameLine();
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[0], 0.1, 1);
					ImGui::Text("Y ");
					ImGui::SameLine();
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[1], 0.1, 1);
					ImGui::Text("Z ");
					ImGui::SameLine();
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[2], 0.1, 1);
				}
				else
				{
					ImGui::Text("X ");
					ImGui::SameLine();
					ImGui::SliderFloat("X##valueXs", &t->getScalePtr()->e[0], 0.1, 1);
					ImGui::Text("Y ");
					ImGui::SameLine();
					ImGui::SliderFloat("Y##valueYs", &t->getScalePtr()->e[1], 0.1, 1);
					ImGui::Text("Z ");
					ImGui::SameLine();
					ImGui::SliderFloat("Z##valueZs", &t->getScalePtr()->e[2], 0.1, 1);
				}
			}
			else //camera
			{
				vec3* t = MainManager::getInstance().getProject()->getCurrentScene()->getCamPTR()->getPosPTR();
				
				ImGui::Text("Camera");

				ImGui::Text("Position");

				ImGui::Text("X ");
				ImGui::SameLine();
				ImGui::SliderFloat("X##valueXpc", &t->e[0], -20.0, 20.0);
				ImGui::Text("Y ");
				ImGui::SameLine();
				ImGui::SliderFloat("Y##valueYpc", &t->e[1], -20.0, 20.0);
				ImGui::Text("Z ");
				ImGui::SameLine();
				ImGui::SliderFloat("Z##valueZpc", &t->e[2], -20.0, 20.0);
			}

			end();
		}
	}
}
