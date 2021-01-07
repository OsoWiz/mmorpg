#pragma once
/*Model class. It may hold a lot of meshes.*/
#include "Mesh.h"
class Model
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaling;

	Model(glm::vec3 pos = glm::vec3(0.0,0.0,0.0), int ID = -10);
	~Model();

	/*Draws the meshes*/
	void Draw(Shader& shader, const glm::mat4& proj, const glm::mat4& view);
	/*Add the mesh*/
	void AddMesh(Mesh* mesh);
	/*Moves the position by the given vector*/
	void Move(glm::vec3 leap);
	/*Sets the position*/
	void SetPosition(glm::vec3 pos);
	/*Scales this model by the given vector*/
	void Scale(glm::vec3 scaling);
	/*Sets the scaling*/
	void SetScaling(glm::vec3 scaling);
	/*Rotates the models components by the given vector of angles*/
	void Rotate(glm::vec3 rotation);
	/*Rotates the whole model and all of its meshes relative to it*/
	void RotateWhole(glm::vec3 rotation);
	/*Sets the rotation*/
	void SetRotation(glm::vec3 rotation);
	/*Returns the id*/
	int GetId();
	/*Sets the id*/
	void SetId(int ID);

protected:
	std::vector<Mesh*> meshes;
	int id;

};

