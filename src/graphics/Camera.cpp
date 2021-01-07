#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up, glm::vec3 dir) :position(pos), direction(dir), upDirection(up),currentYawAngle(0.0),currentPitchAngle(0.0) {
	rightDirection = glm::normalize(glm::cross(direction, upDirection));
}


void Camera::Move(glm::vec3 leap)
{
	position += leap;
}
void Camera::SetPosition(glm::vec3 location)
{
	this->position = location;
}

glm::mat4 Camera::GetCurrentView()
{
	return glm::lookAt(this->position, this->position + this->direction, this->upDirection);
}

void Camera::Yaw(float rotation, glm::vec3& targetPos)
{
	glm::vec3 centeredPos = this->position - targetPos;
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),glm::radians(rotation),glm::vec3(0.0,1.0,0.0));
	glm::vec3 rotatedPos = rotationMatrix * glm::vec4(centeredPos,1);
	glm::vec3 newPos = rotatedPos + targetPos;
	this->position = newPos;
	this->direction = rotationMatrix * glm::vec4(this->direction,1); 
	this->upDirection = rotationMatrix * glm::vec4(this->upDirection, 1);
	this->rightDirection = rotationMatrix * glm::vec4(this->rightDirection, 1);

	this->currentYawAngle = this->currentYawAngle + rotation;
}

void Camera::Pitch(float rotation, glm::vec3& targetPos)
{
	float yaw = this->currentYawAngle;
	this->Yaw(-this->currentYawAngle, targetPos);
	glm::vec3 centeredPos = this->position - targetPos;
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1.0, 0.0, 0.0));
	glm::vec3 rotatedPos = rotationMatrix * glm::vec4(centeredPos, 1);
	glm::vec3 newPos = rotatedPos + targetPos;
	this->position = newPos;
	this->direction = rotationMatrix * glm::vec4(this->direction, 1);
	this->upDirection = rotationMatrix * glm::vec4(this->upDirection, 1);
	this->rightDirection = rotationMatrix * glm::vec4(this->rightDirection, 1);
	this->Yaw(yaw, targetPos);
}

void Camera::ZoomIn(float amount)
{
	this->position += this->direction * amount;
}

void Camera::ZoomOut(float amount)
{
	this->position -= this->direction * amount;
}

float Camera::GetYaw()
	{
	return currentYawAngle;
	}
float Camera::GetPitch()
{
	return currentPitchAngle;
}