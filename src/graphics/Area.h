#pragma once

#include "Terrain.h"
#include "AreaObject.h"
#include "Cubemap.h"
#include <algorithm>
/*Area has a terrain and the meshes needed to populate it with trees, mining nodes, houses, etc.*/
class Area
{
private:
	
	std::vector<AreaObject*> objects;
	Terrain* terrain;
	Cubemap* skybox;
public:
	/*Constructor, takes a terrain and a skybox*/
	Area(Terrain* terde,Cubemap* boxi);

	~Area();
	/*Returns one of the objects stored identified by it's location*/
	AreaObject* ObjectByLocation(glm::vec3 lokaatio);

	/*DrawArea function needs all 3 shaders in order to draw. First the regular modelshader and then the appropriate terrainshader.*/
	void DrawArea(Shader& shader, Shader& terrainShader, Shader& skyboxShader, glm::mat4 proj, glm::mat4 view);
	/*Adds an object to the area.*/
	void AddObject(AreaObject* objekti);
};

