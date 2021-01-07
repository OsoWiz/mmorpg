#pragma once
#include "Model.h"
#include "Camera.h"
#include "GLFW/glfw3.h"
#include "cmath"
#include <stdlib.h>
/*Player class that inherits from the model class. Represents the one who plays.*/
class Player:public Model
{
private:
	 int id;

public:
	Camera camera;
	

	Player(glm::vec3 pos = glm::vec3(0.0, 0.5, 0.0), const int id = -1);

	/*Draws*/
	void Draw(Shader& shader, glm::mat4& proj);
	/*Sets the position*/
	void SetPosition(glm::vec3 location);
	/*Moves*/
	void Move(glm::vec3 leap);
	/*Pitches the camera*/
	void Pitch(float angle);
	/*Yaws the camera*/
	void Yaw(float angle);
	/*Returns the id of the player*/
	int GetId();
	/*Sets the id of the player*/
	void SetId(int ID);
	/*Returns the world coordinates calculated from the mouse click. Very proud of this one*/
	glm::vec2 getMouseRayCoordinate(glm::vec4 initialRay,glm::mat4 proj);
	/*Returns the first mesh on the meshlist*/
	Mesh* GetFirstMesh();
	

};

