#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Material.h"
namespace Trixs
{

class ModelLoader
{
public:
	static Mesh* LoadMesh(std::string path, Material* mat);
};

	
}