#include "Mesh.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyObjLoader.h"
#include "Lambertian.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <chrono>  // for high_resolution_clock

#include "objLoader.h"
namespace Trixs
{

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* matPtr, std::string filePath, vec3 min, vec3 max)
	{
		this->filepath = filePath;
		this->vertices = vertices;
		this->indices = indices;
		this->matPtr = std::move(matPtr);
		nTriangles = triangles.size();
		boundingBox = aabb(min, max);
		root = BvhMesh(min, max, 0);
		triangulated = false;
		init();
	}


	void Mesh::triangulate()
	{
		if (triangulated)
		{
			return;
		}
		triangulated = true;
		for (auto i = 0; i < indices.size(); i+=3)
		{
			triangles.emplace_back(Triangle(indices[i], indices[i+1], indices[i+2], &vertices, this->matPtr));
		}
		nTriangles = triangles.size();
		//todo merge loops

		// Record start time
		auto start = std::chrono::high_resolution_clock::now();

		for (auto i = 0; i < triangles.size(); i++)
		{
			triangles.at(i).setVerticesPointer(&this->vertices);
			root.addTriangle(&triangles.at(i));
		}
		// Record end time
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << "Elapsed time: " << elapsed.count() << " s\n";
	}

	bool Mesh::init()
	{
		//init opengl buffers etc.

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
		//	glBufferData(GL_ARRAY_BUFFER, vertexNormals.size() * sizeof(vec3), &vertexNormals[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//vertex
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		return true;
	}

	std::string Mesh::writeVec3(vec3 v)
	{
		return std::to_string(v.x()) + " " + std::to_string(v.y()) + " " + std::to_string(v.z());
	}

	bool Mesh::hit(const Ray & r, float t_min, float t_max, hitRecord & rec) const
	{
		return root.hit(r, t_min, t_max, rec);
	}

	std::string Mesh::getWritable()
	{
		std::string writable;
		writable.append("MESH\n");
		writable.append(filepath + "\n");
		writable.append("POSITION " + writeVec3(getTransform()->getPos()) + "\n");
		writable.append("ROTATION " + writeVec3(getTransform()->getRot()) + "\n");
		writable.append("SCALE " + writeVec3(getTransform()->getScale()) + "\n");
		writable.append(matPtr->getWritable());
		return writable;
	}

	void Mesh::draw() const
	{
		//opengl draw
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, indices.size());
		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
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
