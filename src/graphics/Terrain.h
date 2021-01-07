#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
class Terrain
{
public:
	std::vector<TerrainVertex> vertices;
	std::vector<Texture*> texturelist;
	Terrain(glm::vec2 location = glm::vec2(0.0,0.0));
	~Terrain();
	/*Returns a boolean indicating wether adding the texture succeeded*/
	bool addTexture(const std::string& texturefilepath);
	/*Sets the blendmap*/
	bool setBlendmap(const std::string& texturefilepath);
	/*Draws this terrain*/
	void DrawTerrain(Shader& terrainShader, const glm::mat4& projection, const glm::mat4& view);

private:
	unsigned int terrainVAO;
	VertexBuffer* terrainVBO;
	Texture* blendmap;

	unsigned int nroVertices;
	unsigned int sidelength = 64;
	unsigned int tilelength = 1;

};

