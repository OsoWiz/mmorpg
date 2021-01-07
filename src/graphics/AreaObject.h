#pragma once
#include "Mesh.h"
#include "Texture.h"
/*3D object designed to be part of an area.*/
class AreaObject
{
public:
	/*Constructor takes in two meshes, texturefilepath, and a type.*/
	AreaObject(Mesh* meshi, Mesh* altmeshi, const std::string filepath, const std::string& tyyppi);
	~AreaObject();
	/*Draws the object*/
	void Draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view);
	/*Draws the alternate object (for example the chopped down tree.)*/
	void DrawAlternate(Shader& shader, const glm::mat4& projection, const glm::mat4& view);
	/*Returns the type variable given to it. Can be used as a status, hence the name*/
	std::string GetStatus();
	/*returns the primary mesh*/
	Mesh* GetMesh();

private:
	Mesh* mesh;
	Mesh* altmesh;
	//Texture* texture;
	const std::string type;
	std::string status;
};

