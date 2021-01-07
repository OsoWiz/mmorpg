#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
/*Vertexbuffer class. Holds vertices in the GPU*/
class VertexBuffer
{
private:
	unsigned int id;
public:
	VertexBuffer(const std::vector<Vertex>& data);
	/*Overloaded constructor for terrainvertices*/
	VertexBuffer(const std::vector<TerrainVertex>& data);
	~VertexBuffer();
	/*Binds this buffer*/
	void Bind();
	/*Unbinds this buffer*/
	void Unbind();
};

