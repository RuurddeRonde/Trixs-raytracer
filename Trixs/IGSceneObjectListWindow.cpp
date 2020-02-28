#include "IGSceneObjectListWindow.h"
#include "MainManager.h"
#include "ViewportCamera.h"
#include "Lambertian.h"
#include "Dielectric.h"
#include "Metal.h"
#include "diffuseLight.h"
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

			static int selected = -1;

			ImGui::BeginChild("Objects", ImVec2(ImGui::GetWindowWidth() - 10, 250), false);

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

			if (selected != -1 && objects->size() > 0) //there has to be an object
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
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[0], 1.0f, 10.0f);
					ImGui::Text("Y ");
					ImGui::SameLine();
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[1], 1.0f, 10.0f);
					ImGui::Text("Z ");
					ImGui::SameLine();
					ImGui::SliderFloat("##valuese", &t->getScalePtr()->e[2], 1.0f, 10.0f);
				}
				else
				{
					ImGui::Text("X ");
					ImGui::SameLine();
					ImGui::SliderFloat("X##valueXs", &t->getScalePtr()->e[0], 1.0f, 10.0f);
					ImGui::Text("Y ");
					ImGui::SameLine();
					ImGui::SliderFloat("Y##valueYs", &t->getScalePtr()->e[1], 1.0f, 10.0f);
					ImGui::Text("Z ");
					ImGui::SameLine();
					ImGui::SliderFloat("Z##valueZs", &t->getScalePtr()->e[2], 1.0f, 10.0f);
				}

				ImGui::Text("Material:");
				ImGui::SameLine();
				Material* mat = objects->at(selected)->getMaterial();
				Lambertian* l = dynamic_cast<Lambertian*>(mat);
				if (l != nullptr) //material is lambertian
				{
					ImGui::Text("Lambertian");
					ImGui::ColorEdit3("Color", l->getAlbedo()->e);
				}
				else
				{
					Metal* m = dynamic_cast<Metal*>(mat);
					if (m != nullptr) //material is metal
					{
						ImGui::Text("Metal");
						ImGui::ColorEdit3("Color", m->getAlbedo()->e);
						ImGui::InputFloat("Fuzz", m->getFuzz(), 0.0f, 1000.0f);
					}
					else
					{
						Dielectric* d = dynamic_cast<Dielectric*>(mat);
						if (d != nullptr) //material is dielectric
						{
							ImGui::Text("Dielectric");
							ImGui::SliderFloat("refractive index", d->getRef(), 0.0f, 10.0f);
						}
						else
						{
							diffuseLight* dl = dynamic_cast<diffuseLight*>(mat);
							if (d != nullptr) //material is diffuse light
							{
								ImGui::Text("diffuse light");
								ImGui::ColorEdit3("refractive index", dl->getEmit()->e);
							}
						}
					}
				}
				static int type = 0;
				ImGui::Combo("Material type:", &type, "Lambertian\0Metal\0Dielectric\0Diffuse light\0");
				if (ImGui::Button("Set"))
				{
					switch (type)
					{
					case 0:
						objects->at(selected)->setMaterial(new Lambertian(vec3(0.3f, 0.4f, 0.3f)));
						break;
					case 1:
						objects->at(selected)->setMaterial(new Metal(vec3(0.1f, 0.1f, 0.1f), 0.1f));
						break;
					case 2:
						objects->at(selected)->setMaterial(new Dielectric(1.5f));
						break;
					case 3:
						objects->at(selected)->setMaterial(new diffuseLight(new vec3(1.0f, 1.0f, 1.0f)));
						break;
					default:
						break;
					}
				}

			}
			else //camera
			{
				vec3* t = MainManager::getInstance().getProject()->getCurrentScene()->getCamPTR()->getPosPTR();
				Camera* cam = MainManager::getInstance().getProject()->getCurrentScene()->getCamPTR();
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

				ImGui::Spacing();
				static float vfov = 90.0f;
				//static float aspect;
				static float aperture = 0.1f;
				static float focus_dist= 8.0f;

				ImGui::SliderFloat("FOV", &vfov, 10.0f, 120.0f);
				ImGui::SliderFloat("Aperture", &aperture, 0.001f, 1.0f);
				ImGui::SliderFloat("Focus distance", &focus_dist, 1.0f, 120.0f);

				if (ImGui::Button("Set!"))
				{
					cam->resetCamera(
						vec3(ViewportCamera::getInstance().Position.x, ViewportCamera::getInstance().Position.y, ViewportCamera::getInstance().Position.z),
						vec3(ViewportCamera::getInstance().Front.x, ViewportCamera::getInstance().Front.y, ViewportCamera::getInstance().Front.z),
						vec3(ViewportCamera::getInstance().Up.x, ViewportCamera::getInstance().Up.y, ViewportCamera::getInstance().Up.z), vfov, 2.0, aperture, focus_dist);
				}
			}

			end();
		}
	}
}
