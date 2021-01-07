#pragma once
#include <GL/glew.h>
#include <vector>
/*Indexbuffer class. Takes in a vector of indices and count of elements*/
class IndexBuffer
{
private:
	unsigned int id;
	size_t s_count;
public:
	IndexBuffer(const std::vector<unsigned int> data, size_t count);
	~IndexBuffer();
	/*Gets the count of the elements*/
	size_t GetCount() const;

	/*Binds this buffer, as the current indexbuffer for drawelements call. Remember to swap in the right one.*/
	void Bind();
	/*Unbinds this buffer from the current slot*/
	void Unbind();
};

