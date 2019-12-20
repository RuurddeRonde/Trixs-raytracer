#pragma once
#include "IGShowImageWindow.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION

#include "external\stb_image.h"
namespace Trixs
{
	void IGShowImageWindow::setNewImage(std::string imagepath)
	{
		bool ret = LoadTextureFromFile(imagepath.c_str(), &my_image_texture, &my_image_width, &my_image_height);

	}

	void IGShowImageWindow::update()
	{
		if (show)
		{
			if (!begin("ShowRenders"))
			{
				end();
			}
			else
			{
				ImGui::SetWindowSize(ImVec2(my_image_width, my_image_height));
				ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowHeight()));
				end();
			}
		}
	}
	bool IGShowImageWindow::LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
	{
		// Load from file
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create a OpenGL texture identifier
		GLuint image_texture;
		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		// Setup filtering parameters for display
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Upload pixels into texture
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		stbi_image_free(image_data);

		*out_texture = image_texture;
		*out_width = image_width;
		*out_height = image_height;

		return true;
	}
	bool IGShowImageWindow::begin(std::string name)
	{
		return ImGui::Begin(name.c_str(), &show, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
	}
}