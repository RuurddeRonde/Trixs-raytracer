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
			ImGui::TreeNodeEx(MainManager::getInstance().getProject()->getCurrentScene()->getName().c_str(), ImGuiTreeNodeFlags_Leaf);
			for (int obj_i = 0; obj_i < objects->size(); obj_i++)
			{
				ImGui::PushID(obj_i);
				std::string id = "Object" + std::to_string(obj_i);//todo add mesh name
				bool node_open = ImGui::TreeNodeEx(id.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s_%u", "hitable", obj_i);
				if (node_open)
				{
					Transform* t = objects->at(obj_i)->getTransform();
					
					ImGui::Text("Position");

					ImGui::Text("X ");
					ImGui::SameLine();
					ImGui::SliderFloat("X##valueXp", &t->getPosPtr()->e[0], -200, 200);
					ImGui::Text("Y ");
					ImGui::SameLine();
					ImGui::SliderFloat("Y##valueYp", &t->getPosPtr()->e[1], -200, 200);
					ImGui::Text("Z ");
					ImGui::SameLine();
					ImGui::SliderFloat("Z##valueZp", &t->getPosPtr()->e[2], -200, 200);

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
				ImGui::PopID();
			}
			ImGui::PopID();
			end();
		}
	}
}
