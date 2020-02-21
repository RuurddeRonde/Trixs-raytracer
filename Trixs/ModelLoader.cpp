#include "ModelLoader.h"
#include <iostream>
#include <vector>

#include <chrono>
namespace Trixs
{
	Mesh* ModelLoader::LoadMesh(std::string path, Material* mat)
	{
		auto start = std::chrono::high_resolution_clock::now();
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
		vec3 max(FLT_MIN, FLT_MIN, FLT_MIN);
		vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
		vertices.resize(mesh->mNumVertices);
		// Walk through each of the mesh's vertices
		Vertex vertex;
		vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// positions
			vector.e[0] = mesh->mVertices[i].x;
			vector.e[1] = mesh->mVertices[i].y;
			vector.e[2] = mesh->mVertices[i].z;
			vertex.Position = vector;

			if (vector.e[0] < min.x()) { min.setx(vector.e[0]); }
			else if (vector.e[0] > max.x()) { max.setx(vector.e[0]); }
			if (vector.e[1] < min.y()) { min.sety(vector.e[1]); }
			else if (vector.e[1] > max.y()) { max.sety(vector.e[1]); }
			if (vector.e[2] < min.z()) { min.setz(vector.e[2]); }
			else if (vector.e[2] > max.z()) { max.setz(vector.e[2]); }

			if (mesh->HasNormals())
			{
				// normals
				vector.e[0] = mesh->mNormals[i].x;
				vector.e[1] = mesh->mNormals[i].y;
				vector.e[2] = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			vertices.emplace_back(vertex);
		}
		std::vector<Triangle> triangles;


		// Record start time

		// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.emplace_back(face.mIndices[j]);
			}
			//todo add normals
			triangles.emplace_back(Triangle(face.mIndices[0], face.mIndices[1], face.mIndices[2], &vertices, mat));
		}

		// Record end time
		auto finish = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << " s\n";

		return new Mesh(vertices, indices, triangles, mat, path, min, max);
	}


	Mesh* ModelLoader::LoadMesh(std::string path, Material* mat, Transform t)
	{
		Mesh* m = LoadMesh(path, mat);
		m->setStartTransform(t);
		return m;
	}

}