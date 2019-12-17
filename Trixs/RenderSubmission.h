#pragma once
namespace Trixs
{
	class Scene;
	struct RenderSubmission
	{
		int width;
		int height;
		int samplesPerPixel;
		std::string outputfile;
		Scene* scene;
	};
}