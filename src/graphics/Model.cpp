#include "Model.h"

Model::Model(glm::vec3 pos, int ID):position(pos),rotation(glm::vec3(0.0,0.0,0.0)),scaling(glm::vec3(1.0f)),id(ID)
{

}

Model::~Model() {
	for (auto& i : meshes) {
		i->~Mesh();
	}
}

void Model::Draw(Shader& shader,const glm::mat4& proj, const glm::mat4& view) {
	for (auto& i : meshes) {
		i->Draw(shader,proj,view);
	}
}

void Model::AddMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
	this->SetPosition(this->position);
}

void Model::Move(glm::vec3 leap) {
	this->position += leap;

	for (auto& i : meshes) {
		i->Move(leap);
	}
}

void Model::SetPosition(glm::vec3 pos) {
	this->position = pos;
	//i's Position is the relative position to the model. The base model should always be at the same position as the model itself and others whereever they desire.
	for (auto& i : meshes) {
		i->SetPosition(pos);
	}
}


void Model::Scale(glm::vec3 scaling) {
	this->scaling += scaling;
	for (auto& i : meshes) {
		i->Scale(scaling);
	}
}

void Model::SetScaling(glm::vec3 scaling) {
	this->scaling = scaling;
	for (auto& i : meshes) {
		i->SetScaling(scaling);
	}
}

void Model::Rotate(glm::vec3 rotation) {
	this->rotation = rotation;
	for (auto& i : meshes) {
		i->Rotate(rotation);
	}
}
void Model::RotateWhole(glm::vec3 rotation) {
	this->rotation = rotation;
	for (auto& i : meshes) {
		i->RotateRelative(rotation,this->position);
	}
}

void Model::SetRotation(glm::vec3 rotation) {

	for (auto& i : meshes) {
		i->SetRotation(rotation);
	}
}

int Model::GetId()
{
	return this->id;
}

void Model::SetId(int ID)
{
	this->id = ID;
}