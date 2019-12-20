#pragma once
#include "ImGuiWindow.h"
namespace Trixs
{

	class IGShowImageWindow : public ImGuiWindow
	{
	public:
		void update() override;
		bool begin(std::string name) override;
		void setNewImage(std::string imagepath);
	private:

		int my_image_width = 0;
		int my_image_height = 0;
		GLuint my_image_texture = 0;

		bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
	};

}