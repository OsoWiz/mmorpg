#include "Area.h"


Area::Area(Terrain* terde, Cubemap* boxi) :terrain(terde), skybox(boxi)
{

}

Area::~Area()
{
	for (auto& i : objects) {
		i->~AreaObject();
	 }

	this->terrain->~Terrain();
	this->skybox->~Cubemap();
}

AreaObject* Area::ObjectByLocation(glm::vec3 lokaatio)
{
	auto vastaus = std::find_if(this->objects.begin(), this->objects.end(), [=](AreaObject* a) {return a->GetMesh()->position == lokaatio; });
	return *vastaus;
}

void Area::AddObject(AreaObject* objekti)
{
	this->objects.push_back(objekti);
}

void Area::DrawArea(Shader& shader, Shader& terrainShader, Shader& skyboxShader, glm::mat4 proj, glm::mat4 view)
{
	/*Useful to draw a treestump when tree is cut down for example.*/
	for (auto& i : objects) {
		if(i->GetStatus() == "ok")i->Draw(shader,proj,view);
		else i->DrawAlternate(shader, proj, view);
	}
	this->terrain->DrawTerrain(terrainShader, proj, view);
	this->skybox->Draw(skyboxShader, proj, view);

}