#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <vector>
#include <stb_image.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
class Cubemap
{
private:
	unsigned int id;
	unsigned int VAO;
	//Cannot use regular vbo class due to us requiring only 3 floats
	unsigned int VBO;
	IndexBuffer* IBO;
	int height_;
	int width_;
	int channels;
public:
	Cubemap(std::vector<unsigned char*> images, int width, int height, int nrofChannels);
	~Cubemap();
	/*Getter for id*/
	unsigned int GetId();
	/*Getter for image width*/
	int Width();
	/*Getter for image height*/
	int Height();
	/*Draws the cubemap*/
	void Draw(Shader& cubemapShader,glm::mat4 proj, glm::mat4 view);
	/*Activates the given texture unit*/
	void Activate(const int& slot);
	/*This bind command apparently already sets up the sampler ready in the fragmentshader.*/
	void Bind();
	/*Unbinds this*/
	void Unbind();
	/*deactivates the slot*/
	void Deactivate();
};

