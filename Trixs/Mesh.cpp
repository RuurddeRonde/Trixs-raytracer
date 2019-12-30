#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyObjLoader.h"
#include "Lambertian.h"
namespace Trixs
{
	Mesh::Mesh(std::string filepath, Material* matPtr)
	{
		this->matPtr = matPtr;
		this->filepath = filepath;
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str());

		if (!warn.empty()) {
			std::cout << warn << std::endl;
		}

		if (!err.empty()) {
			std::cerr << err << std::endl;
		}

		if (!ret) {
			return;
		}

		vec3 max(FLT_MIN, FLT_MIN, FLT_MIN);
		vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);

		this->nVertices = attrib.vertices.size();
		int vp = 0; //vertex iterator
		int tr = 0; //triangle iterator
		int tvc = 0; //count to 3

		for (auto i = 0; i <= attrib.vertices.size() - 3; i += 3)//copy vertex
		{
			vertexPositions.push_back(vec3(attrib.vertices.at(i), attrib.vertices.at(i + 1), attrib.vertices.at(i + 2)));
		}
		bool hasNormals = true;
		if (attrib.normals.size() != 0)
		{
			for (auto i = 0; i <= attrib.normals.size() - 3; i += 3)//copy normals
			{
				vertexNormals.push_back(vec3(attrib.normals.at(i), attrib.normals.at(i + 1), attrib.normals.at(i + 2)));
			}
		}
		else
		{
			hasNormals = false;
		}

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				if (fv == 3)//shape is a triangle
				{
					int cornera = shapes[s].mesh.indices[index_offset + 0].vertex_index;
					int cornerb = shapes[s].mesh.indices[index_offset + 1].vertex_index;
					int cornerc = shapes[s].mesh.indices[index_offset + 2].vertex_index;

					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + 0];
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];

					if (vx < min.x()) { min.setx(vx); }
					if (vx > max.x()) { max.setx(vx); }
					if (vy < min.y()) { min.sety(vy); }
					if (vy > max.y()) { max.sety(vy); }
					if (vz < min.z()) { min.setz(vz); }
					if (vz > max.z()) { max.setz(vz); }

					if (hasNormals)
					{
						tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
						tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
						tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
						triangles.push_back(Triangle(cornera, cornerb, cornerc, &vertexPositions, vec3(nx, ny, nz),matPtr));
					}
					else
					{
						triangles.push_back(Triangle(cornera, cornerb, cornerc, &vertexPositions, matPtr));
					}

				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}
		boundingBox = aabb(min, max);
		root = BvhMesh(min, max, 0);
		for (auto i = 0; i < triangles.size(); i++)
		{
			root.addTriangle(&triangles.at(i));
		}
	}

	bool Mesh::hit(const Ray & r, float t_min, float t_max, hitRecord & rec) const
	{
		return root.hit(r, t_min, t_max, rec);
	}

	std::string Mesh::getWritable() const
	{
		std::string writable;
		writable.append("MESH\n");
		writable.append(matPtr->getWritable());
		writable.append(filepath);
		return writable;
	}


	BvhMesh::BvhMesh(const vec3 aa, const vec3 bb, int depth)
	{
		this->depth = depth;
		this->boundingBox = aabb(aa, bb);
		ltf = nullptr;
		ldf = nullptr;
		ltb = nullptr;
		ldb = nullptr;
		rtf = nullptr;
		rtb = nullptr;
		rdf = nullptr;
		rdb = nullptr;

	}
	bool BvhMesh::hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const
	{

		if (!boundingBox.hit(r, t_min, t_max))
		{
			return false;
		}
		if (ltf != nullptr)
		{
			return ltf->hit(r, t_min, t_max, rec) ||
				ldf->hit(r, t_min, t_max, rec) ||
				ltb->hit(r, t_min, t_max, rec) ||
				ldb->hit(r, t_min, t_max, rec) ||
				rtf->hit(r, t_min, t_max, rec) ||
				rtb->hit(r, t_min, t_max, rec) ||
				rdf->hit(r, t_min, t_max, rec) ||
				rdb->hit(r, t_min, t_max, rec);

		}
		else //hit with no children
		{
			hitRecord temp_rec;
			bool hit_anything = false;
			double closest_so_far = t_max;
			for (int i = 0; i < triangles.size(); i++) {
				if (triangles.at(i)->hit(r, t_min, closest_so_far, temp_rec)) {
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return hit_anything;
		}
	}
	void BvhMesh::addTriangle(Triangle* newtri)
	{
		if (ltf == nullptr) //no childeren
		{
			triangles.push_back(newtri);
			if (triangles.size() > maxTriangles && this->depth < maxDivisions)
			{
				float aax = boundingBox.min().x();
				float aay = boundingBox.min().y();
				float aaz = boundingBox.min().z();
				float bbx = boundingBox.max().x();
				float bby = boundingBox.max().y();
				float bbz = boundingBox.max().z();
				float halfx = (bbx - aax) / 2;
				float halfy = (bby - aay) / 2;
				float halfz = (bbz - aaz) / 2;
				//create children
				ldf = new BvhMesh(vec3(aax, aay, aaz), vec3(bbx - halfx, bby - halfy, bbz - halfz), this->depth + 1);
				ltf = new BvhMesh(vec3(aax, aay + halfy, aaz), vec3(bbx - halfx, bby, bbz - halfz), this->depth + 1);
				rdf = new BvhMesh(vec3(aax + halfx, aay, aaz), vec3(bbx, bby - halfy, bbz - halfz), this->depth + 1);
				rtf = new BvhMesh(vec3(aax + halfx, aay + halfy, aaz), vec3(bbx, bby, bbz - halfz), this->depth + 1);
				ltb = new BvhMesh(vec3(aax, aay + halfy, aaz + halfz), vec3(bbx - halfx, bby, bbz), this->depth + 1);
				ldb = new BvhMesh(vec3(aax, aay, aaz + halfz), vec3(bbx - halfx, bby - halfy, bbz), this->depth + 1);
				rtb = new BvhMesh(vec3(aax + halfx, aay + halfy, aaz + halfz), vec3(bbx, bby, bbz), this->depth + 1);
				rdb = new BvhMesh(vec3(aax + halfx, aay, aaz + halfz), vec3(bbx, bby - halfy, bbz), this->depth + 1);
				//add triangles to children recursive
				for (auto i = 0; i < triangles.size(); i++)
				{
					this->addTriangle(triangles.at(i));
				}
				triangles.clear();
			}
		}
		else //add triangle to child
		{
			bool addedtosomething = false;
			//if the tri at any point intersects with the child it will be added
			if (ltf->boundingBox.collide(newtri->getBoundingBox()))
			{
				ltf->addTriangle(newtri);
				addedtosomething = true;
			}
			if (ldf->boundingBox.collide(newtri->getBoundingBox()))
			{
				ldf->addTriangle(newtri);
				addedtosomething = true;
			}
			if (ltb->boundingBox.collide(newtri->getBoundingBox()))
			{
				ltb->addTriangle(newtri);
				addedtosomething = true;
			}
			if (ldb->boundingBox.collide(newtri->getBoundingBox()))
			{
				ldb->addTriangle(newtri);
				addedtosomething = true;
			}
			if (rtf->boundingBox.collide(newtri->getBoundingBox()))
			{
				rtf->addTriangle(newtri);
				addedtosomething = true;
			}
			if (rtb->boundingBox.collide(newtri->getBoundingBox()))
			{
				rtb->addTriangle(newtri);
				addedtosomething = true;
			}
			if (rdf->boundingBox.collide(newtri->getBoundingBox()))
			{
				rdf->addTriangle(newtri);
				addedtosomething = true;
			}
			if (rdb->boundingBox.collide(newtri->getBoundingBox()))
			{
				rdb->addTriangle(newtri);
				addedtosomething = true;
			}
			if (!addedtosomething)
			{
				//error;
				std::cout << "error: invalid triangle added to bvhmesh" << std::endl;
			}
		}
	}
}
