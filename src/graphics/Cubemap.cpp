#include "Cubemap.h"


Cubemap::Cubemap(std::vector<unsigned char*> images, int width, int height, int nrofChannels) : width_(width), height_(height), channels(nrofChannels)
{

	//Maybe call glactivetexture here to activate the right texture unit. But which one is the right one?
	float vertices[24] = {
	-1,1,1,
	 1,1,1,
	 1,1,-1,
	-1,1,-1,
	-1,-1,1,
	 1,-1,1,
	 1,-1,-1,
	-1,-1,-1
	};
	


	std::vector<unsigned int> indices = {
	2,3,7, //1
	6,2,7, //2
	3,0,4, //3
	7,3,4, //4
	1,2,6, //5
	5,1,6, //6
	0,1,5, //7
	4,0,5, //8
	1,3,2, //9
	0,3,1, //10
	4,5,6, //11
	4,6,7  //12
	};


	//TODO: Add vao, vbo and a ibo.
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,3*8*sizeof(float),vertices,GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, 3 * 6*6 * sizeof(float), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	this->IBO = new IndexBuffer(indices, indices.size());

	
	//Generate the texture.
	glGenTextures(1, &id);
	//Bind this as gl  cubemap texture. So it's in that slot now, as it was the last thing bound.
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	//default options on constructor. TODO: additional option functions for this class to change these settings.
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < images.size(); i++)
	{
		auto data = images[i];
		//This is what actually generates the texture on the currently bound object.
		if (nrofChannels == 3) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nrofChannels == 4) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}
	//Generate mipmap?
	//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	//Slight debug keis
	//std::cout <<"Indeksejä on skyboksissa: "<< this->IBO->GetCount() << std::endl;
	//Unbind vao
	glBindVertexArray(0);
}

Cubemap::~Cubemap()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1,&this->VBO);
	glDeleteTextures(1, &id);
}

void Cubemap::Draw(Shader& cubemapShader, glm::mat4 proj, glm::mat4 view)
{
	cubemapShader.Use();
	glm::mat4 diminishedView = glm::mat4(glm::mat3(view));
	glm::mat4 final = proj * diminishedView;
	//cubemapShader.SetMat4("cubemap",final);
	cubemapShader.SetMat4("proj",proj);
	cubemapShader.SetMat4("view",diminishedView);
	glBindVertexArray(VAO);
	this->Activate(GL_TEXTURE0);
	this->Bind();
	
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_TRIANGLES, unsigned int(IBO->GetCount()), GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);

	//Cleaning up

	glBindVertexArray(0);
	this->Deactivate();
	this->Unbind();
	cubemapShader.Unuse();
}


unsigned int Cubemap::GetId()
{
	return id;
}
int Cubemap::Width()
{
	return width_;
}
int Cubemap::Height()
{
	return height_;
}


void Cubemap::Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
}
void Cubemap::Unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::Activate(const int& slot)
{
	glActiveTexture(slot);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}
void Cubemap::Deactivate()
{
	glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}