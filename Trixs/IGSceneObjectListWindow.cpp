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
			ImGui::TreeNodeEx("sceneObjects", ImGuiTreeNodeFlags_Leaf);
			for (int obj_i = 0; obj_i < objects->size(); obj_i++)
			{
				ImGui::PushID(obj_i);
				std::string id = "Object" + std::to_string(obj_i);
				bool node_open = ImGui::TreeNodeEx(id.c_str(), ImGuiTreeNodeFlags_NoTreePushOnOpen, "%s_%u", "hitable", obj_i);
				if (node_open)
				{
					Transform* t = objects->at(obj_i)->getTransform();
					ImGui::SliderFloat("X##valueX", &t->getPosPtr()->e[0], -200, 200);
					ImGui::SliderFloat("Y##valueY", &t->getPosPtr()->e[1], -200, 200);
					ImGui::SliderFloat("X##valueZ", &t->getPosPtr()->e[2], -200, 200);

				}
				ImGui::PopID();
			}
			ImGui::PopID();
			end();
		}
	}
}
