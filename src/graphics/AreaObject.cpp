#include "AreaObject.h"

AreaObject::AreaObject(Mesh* meshi, Mesh* altmeshi, const std::string filepath,const std::string& tyyppi) :mesh(meshi),altmesh(altmeshi), type(tyyppi),status("ok")
{
	this->mesh->addTexture(filepath);
	this->altmesh->addTexture(filepath);
}


AreaObject::~AreaObject() {
	this->mesh->~Mesh();
 }

Mesh* AreaObject::GetMesh()
{
	return this->mesh;
}

std::string AreaObject::GetStatus()
{
	return status;
}

void AreaObject::Draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view)
{
	this->mesh->Draw(shader, projection, view);
}

void AreaObject::DrawAlternate(Shader& shader, const glm::mat4& projection, const glm::mat4& view)
{
	this->altmesh->Draw(shader, projection, view);
}
