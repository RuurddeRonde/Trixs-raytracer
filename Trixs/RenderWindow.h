#pragma once
#include "ImGuiWindow.h"
#include "RayTrixser.h"
namespace Trixs
{

	class IGRenderWindow : public ImGuiWindow
	{
	public:
		void update() override;
		bool hasNewRender()
		{
			if (newImage)
			{
				newImage = false;
				return true;
			}
			return false;
		}
		std::string getLastRenderPath() { return LastRenderPath; }
	private:
		RayTrixser RT;
		int nx = 192;
		int ny = 108;
		int ns = 1;
		bool newImage = true;

		int my_image_width = 0;
		int my_image_height = 0;
		GLuint my_image_texture = 0;
		std::string LastRenderPath = "renders/rendertest.jpg";
		int filetype = 0;
	};

}