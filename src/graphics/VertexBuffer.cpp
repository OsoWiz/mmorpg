
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const std::vector<Vertex>& data)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(Vertex), &data[0], GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const std::vector<TerrainVertex>& data)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(TerrainVertex), &data[0], GL_STATIC_DRAW);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1,&id);
}


void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}