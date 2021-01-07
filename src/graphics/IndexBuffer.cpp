#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const std::vector<unsigned int> data, size_t count): s_count(count)
{
	
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*(sizeof(unsigned int)), &data[0], GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

size_t IndexBuffer::GetCount() const
{
	return s_count;
}

void IndexBuffer::Bind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}