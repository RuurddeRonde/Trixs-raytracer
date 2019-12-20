#pragma once
namespace Trixs
{
	enum FileTypes
	{
		JPG = 0,
		PNG = 1,
		BPM = 2,
		TGA = 3,
		HDR = 4
	};
	class Scene;
	struct RenderSubmission
	{
		int width;
		int height;
		int samplesPerPixel;
		std::string outputfile;
		FileTypes outputType;
		Scene* scene;
	};
}