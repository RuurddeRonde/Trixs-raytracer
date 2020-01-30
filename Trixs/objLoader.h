#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Vec3.h"
#include "Vec2.h"
#include <vector>
#include <string>
namespace Trixs
{

	struct OBJIndex
	{
		unsigned int vertexIndex;
		unsigned int uvIndex;
		unsigned int normalIndex;

		bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
	};

	class IndexedModel
	{
	public:
		std::vector<vec3> positions;
		std::vector<vec2> texCoords;
		std::vector<vec3> normals;
		std::vector<unsigned int> indices;

		void CalcNormals();
	};

	class OBJModel
	{
	public:
		std::vector<OBJIndex> OBJIndices;
		std::vector<vec3> vertices;
		std::vector<vec2> uvs;
		std::vector<vec3> normals;
		bool hasUVs;
		bool hasNormals;

		OBJModel(const std::string& fileName);

		IndexedModel ToIndexedModel();
	private:
		unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
		void CreateOBJFace(const std::string& line);

		vec2 ParseOBJVec2(const std::string& line);
		vec3 ParseOBJVec3(const std::string& line);
		OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
	};


}
#endif