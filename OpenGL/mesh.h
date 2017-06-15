#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"
#include <string>

using namespace std;

//The class to hold the actual data
class Vertex
{
private:
	glm::vec3 pos;//To hold a 3D vertex in the x, y, z coordinate system
	glm::vec2 texCoord;//Texture coordinate in the vertex positions
	glm::vec3 normal;//To hold the normals
public:
	Vertex(const glm::vec3 pos, const glm::vec2 texCoord, const glm::vec3 normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }
	inline glm::vec3* GetNormal() { return &normal; }

};

//The class for process the data into a mesh
class Mesh
{
private:

	void InitMesh(const IndexedModel& model);

	enum//To create a position/value for the NUM_BUFFER
	{
		POSITION_VB,//Begining

		TEXCOORD_VB,

		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFER//End
	};

	GLuint m_vertexArrayObject;//To hold the mesh data!
	GLuint m_vertexArrayBuffers[NUM_BUFFER];//To hold the vertex buffers
	unsigned int m_drawCount;

	

public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);//Passing list of vertex data
	Mesh(const string& fileName);
	virtual ~Mesh();

	//To draw the mesh into the display
	void Draw();

};
#endif