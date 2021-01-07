#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	glm::vec3 position;
	glm::vec2 texture;
	glm::vec3 normal;
};

struct TerrainVertex
{
	glm::vec3 position;
	glm::vec2 texture;
};

//One can add this inside the class if this struct works the way it is.
//Vertex(glm::vec3 pos, glm::vec2 text, glm::vec3 norm):position(pos),texture(text),normal(norm){}
//This is a constructor. But I don't know if it will change the size of the sruct, therefore destroying the use of it in the mesh class.
