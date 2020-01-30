#include "ModelLoader.h"
#include <iostream>
#include <vector>
namespace Trixs
{
	Mesh* ModelLoader::LoadMesh(std::string path, Material* mat)
	{

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		//std::vector<Texture> textures;

		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return nullptr;
		}

		// data to fill
		aiMesh* mesh = scene->mMeshes[0];
		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			// positions
			vector.e[0] = mesh->mVertices[i].x;
			vector.e[1] = mesh->mVertices[i].y;
			vector.e[2] = mesh->mVertices[i].z;
			vertex.Position = vector;
			// normals
			vector.e[0] = mesh->mNormals[i].x;
			vector.e[1] = mesh->mNormals[i].y;
			vector.e[2] = mesh->mNormals[i].z;
			vertex.Normal = vector;
			vertices.push_back(vertex);
		}
		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		return new Mesh(vertices, indices, mat);
	}

}