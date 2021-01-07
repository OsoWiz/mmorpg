#include "Player.h"

Player::Player(glm::vec3 pos, const int id):Model(pos),camera(Camera(this->position + glm::vec3(0.0, 0.0, 10.0))),id(id)
{

}


void Player::Draw(Shader& shader,glm::mat4& proj)
{
	glm::mat4 view = this->camera.GetCurrentView();
	this->Model::Draw(shader,proj,view);
}

void Player::Move(glm::vec3 leap)
{
	this->Model::Move(leap);
	this->camera.Move(leap);
}

void Player::SetPosition(glm::vec3 location)
{
	glm::vec3 offset = this->camera.position - this->position;
	this->Model::SetPosition(location);
	//std::cout << "Camera position before the set: " << " X: " << this->camera.position.x << ", Y: " << this->camera.position.y << ", Z: " << this->camera.position.z << std::endl;
	this->camera.SetPosition(location);
	this->camera.Move(offset);
	//std::cout << "Camera position after the set: " << " X: " << this->camera.position.x << ", Y: " << this->camera.position.y << ", Z: " << this->camera.position.z << std::endl;
}

void Player::Pitch(float angle)
{
	this->camera.Pitch(angle, this->position);
}

glm::vec2 Player::getMouseRayCoordinate(glm::vec4 initialRay, glm::mat4 proj)
{
	glm::vec4 eyeRay = glm::inverse(proj) * initialRay;
	//Reverse the z component so it points out of the camera.
	eyeRay = glm::vec4(eyeRay.x, eyeRay.y, -1.0, 0.0);
	//Normalized worldray :D
	glm::vec4 worldRay = glm::normalize(glm::inverse(this->camera.GetCurrentView()) * eyeRay);
	if (worldRay.y >= 0) {
		return glm::vec2(this->position.x, this->position.z);
	}
	else {
		double kerroin = -1 * this->camera.position.y / (worldRay.y);
		int uusX = int(round(kerroin * worldRay.x + this->camera.position.x));
		int uusZ =  int(round(kerroin * worldRay.z + this->camera.position.z));

		return glm::vec2(uusX, uusZ);
	}
}


void Player::Yaw(float angle)
{
	this->camera.Yaw(angle, this->position);

}
int Player::GetId()
{
	return this->id;
}
void Player::SetId(int ID)
{
	 this->id=ID;
}

Mesh* Player::GetFirstMesh()
{
	return this->meshes[0];
}