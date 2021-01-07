#include "Terrain.h"


Terrain::Terrain(glm::vec2 location):blendmap(nullptr)
{
	nroVertices = 0;

	for (unsigned int i = 0; i < sidelength; i++) {
		for (unsigned int j = 0; j < sidelength; j++) {
			float xoffset = -0.5; //location.x-sidelength/2;
			float zoffset = -0.5;//location.y - sidelength / 2;
			//One tile = 2 triangles = 6 vertices
			//first
			TerrainVertex terra1;
			TerrainVertex terra2;
			TerrainVertex terra3;
			//second
			TerrainVertex terra4;
			TerrainVertex terra5;
			TerrainVertex terra6;

			//All positions
			glm::vec3 pos1 = glm::vec3( tilelength*i+xoffset, 0, tilelength*j+ zoffset);
			glm::vec3 pos2 = glm::vec3(tilelength * i + xoffset, 0, tilelength * (j+1) + zoffset);
			glm::vec3 pos3 = glm::vec3(tilelength * (i + 1) + xoffset, 0, tilelength * j + zoffset);
			glm::vec3 pos4 = glm::vec3(tilelength * (i+1) + xoffset, 0, tilelength * (j + 1) + zoffset);
			//All textcoords
			float lgth = (float)sidelength+1;
			glm::vec2 tex1 = glm::vec2(i/lgth, j / lgth);
			glm::vec2 tex2 = glm::vec2(i / lgth, (j+1) / lgth);
			glm::vec2 tex3 = glm::vec2((i+1) / lgth, j / lgth);
			glm::vec2 tex4 = glm::vec2((i + 1) / lgth, (j + 1) / lgth); 


			//Intitalize
			terra1.position = pos1; terra1.texture = tex1;
			terra2.position = pos2; terra2.texture = tex2;
			terra3.position = pos3; terra3.texture = tex3;
	
			terra4.position = pos4; terra4.texture = tex4;
			terra5.position = pos3; terra5.texture = tex3;
			terra6.position = pos2; terra6.texture = tex2;

			//first
			vertices.push_back(terra1);
			vertices.push_back(terra2);
			vertices.push_back(terra3);
			//second
			vertices.push_back(terra4);
			vertices.push_back(terra5);
			vertices.push_back(terra6);
			//Each tile is 6 triangles
			nroVertices+=6;
		}
	}
	
	

	glGenVertexArrays(1,&terrainVAO);
	glBindVertexArray(terrainVAO);
	terrainVBO = new VertexBuffer(this->vertices);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, texture));

	//Note: YOU DON'T NEED TO UNBIND VBO's or IBO's. UNBINDING VAO IS ENOUGH
	glBindVertexArray(0);

}

Terrain::~Terrain()
{
	
		for (auto iter = texturelist.begin(); iter != texturelist.end(); iter++)
		{
			delete(*iter);
		}
		glDeleteVertexArrays(1, &this->terrainVAO);
		terrainVBO->~VertexBuffer();
	
}


bool Terrain::addTexture(const std::string& texturefilepath)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, nchannels;
	unsigned char* image = stbi_load(texturefilepath.c_str(), &width, &height, &nchannels, 0);

	if (image) {
		Texture* tex = new Texture(image, width, height, nchannels);

		texturelist.push_back(tex);
		stbi_image_free(image);
		return true;
	}
	else {
		stbi_image_free(image);
		return false;
	}
}
bool Terrain::setBlendmap(const std::string& texturefilepath)
{
	stbi_set_flip_vertically_on_load(false);
	int width, height, nchannels;
	unsigned char* image = stbi_load(texturefilepath.c_str(), &width, &height, &nchannels, 0);

	if (image) {
		this->blendmap = new Texture(image, width, height, nchannels);

		stbi_image_free(image);
		return true;
	}
	else {
		stbi_image_free(image);
		return false;
	}
}


void Terrain::DrawTerrain(Shader& terrainShader, const glm::mat4& projection, const glm::mat4& view)
{
	//Literally the first thing you should do. Activate the shader program you are about to use. 
	//This might get moved to the models location, as we want the same shader to draw each of the objects in the model.
	terrainShader.Use();
	glm::mat4 model = projection * view;
	terrainShader.SetMat4("model", model);
	int juttu = this->sidelength;
	terrainShader.SetInt("side",juttu);
	
	this->blendmap->Activate(GL_TEXTURE0);
	unsigned int luku = 0;
	terrainShader.SetUnsint("blendmap", luku);
	glBindTexture(GL_TEXTURE_2D, this->blendmap->GetId());

	for (unsigned int i = 0; i < texturelist.size(); i++)
	{
		texturelist[0]->Activate(GL_TEXTURE1 + i); // activate proper texture unit before binding
		// retrieve texture number 
		std::string number;
		std::string name = "texture";
		unsigned int nro = i + 1;
		number = std::to_string(nro);
		
		terrainShader.SetUnsint((name + number), nro);
		glBindTexture(GL_TEXTURE_2D, texturelist[i]->GetId());
	}

	//This was in some example code
	//glActiveTexture(GL_TEXTURE0);

	// draw mesh first bind this vao so it uses the vbo of this mesh
	glBindVertexArray(terrainVAO);

	
	glDrawArrays(GL_TRIANGLES, 0, nroVertices);
	
	//Unbind stuff
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	terrainShader.Unuse();

}
