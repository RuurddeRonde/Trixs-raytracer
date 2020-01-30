#pragma once
#include "Hitable.h"
#include "Triangle.h"
#include "aabb.h"
#include <vector>
namespace Trixs
{
	constexpr int maxTriangles = 100;
	constexpr int maxDivisions = 5;

	struct Vertex {
		Vertex() {}
		Vertex(vec3 pos, vec3 norm) : Position(pos), Normal(norm) {}
		vec3 Position;
		vec3 Normal;
	};

	class BvhMesh : public Hittable
	{
	public:
		BvhMesh() {}
		BvhMesh(const vec3 aa, const vec3 bb, int depth);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;

		void addTriangle(Triangle* newtri);
	private:
		aabb boundingBox;
		std::vector<Triangle*> triangles;
		int depth;
		BvhMesh* ltf;
		BvhMesh* ltb;
		BvhMesh* ldf;
		BvhMesh* ldb;
		BvhMesh* rtf;
		BvhMesh* rtb;
		BvhMesh* rdf;
		BvhMesh* rdb;
	};

	class Mesh : public Hittable
	{
	public:
		Mesh(std::string filepath, Material* matPtr);
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* matPtr);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
		virtual std::string getWritable()const override;
		virtual void draw() const override;
	private:
		bool init();
		int nIndices;
		int nTriangles;
		int nVertices;
		std::vector<Triangle> triangles;
		std::vector<unsigned int> indices;
		std::vector<Vertex> vertices;
		//std::vector<vec3> vertexPositions;
		//std::vector<vec3> vertexNormals;
		aabb boundingBox;
		BvhMesh root;
		std::string filepath;
		unsigned int VAO, VBO, EBO;
	};
}
