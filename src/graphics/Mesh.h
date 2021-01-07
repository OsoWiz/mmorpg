#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"


/*Mesh that holds vertices*/
class Mesh
{
public:
	/*Value members*/
	std::vector<Vertex> vertices;
	std::vector<Texture*> texturelist;
	
	glm::vec3 position;
	glm::vec3 relativePosition;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 positionMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 meshMatrix;

	/*Creates a mesh from the given objectloader.*/
	Mesh(const std::vector<Vertex>& verts, glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 relPos = glm::vec3(0.0, 0.0, 0.0));
	~Mesh();
	/*Creates a 2dtexture from the filepath*/
	bool addTexture(const std::string& texturefilepath);
	/*Draws this mesh onto the screen using the given shader and the matrices*/
	void Draw(Shader& Shader, const glm::mat4& projection, const glm::mat4& view);
	/*Draws this mesh onto the screen using the given shader and the matrices. This does not update the matrices and thus should be used in the model draw command?*/
	/*Sets the position*/
	void SetPosition(glm::vec3 pos);
	/*Sets the relative position*/
	void SetRelativePosition(glm::vec3 pos);
	/*Sets the rotation*/
	void SetRotation(glm::vec3 rotationToDo);
	/*Sets the scaling*/
	void SetScaling(glm::vec3 scale);
	/*Moves the position by the given vector*/
	void Move(glm::vec3 leap);
	/*Rotates the mesh by the given vector of angles*/
	void Rotate(glm::vec3 rotationToDo);
	/*Rotates relative to the model*/
	void RotateRelative(glm::vec3 rotationToDo, glm::vec3 origin);
	/*Sets the rotation*/
	void SetRotationRelative(glm::vec3 rotationToDo, glm::vec3 origin);
	/*Scales this mesh by the given vector*/
	void Scale(glm::vec3 scale);
	/*Updates the translation matrix*/
	void UpdatePosition();
	/*Updates the rotation matrix*/
	void UpdateRotation();
	/*Updates the scaling matrix*/
	void UpdateScaling();
	/*Updates everything*/
	void UpdateAll();
	/*Returns the specific model matrix that consists of multiple matrices*/
	glm::mat4 GetDrawMatrix(const glm::mat4& projection, const glm::mat4& view);
	/*returns the amount of vertices the mesh has*/
	size_t GetVertices();

private:
	//Vertex array object, vertexbuffer and of course, indexbuffer.
	unsigned int VAO;
	VertexBuffer* VBO;
	size_t nrofVertices;
};

