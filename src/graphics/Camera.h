#pragma once
#include "glm/glm.hpp"
#include "glm/ext.hpp"
class Camera
{
private:
	float currentYawAngle;
	float currentPitchAngle;

public:
	/*Represents the position of the camera*/
	glm::vec3 position;
	/*Represents the direction the camera is facing*/
	glm::vec3 direction;
	/*Represents the direction of which way is up for the camera*/
	glm::vec3 upDirection;
	/*Represents a vector pointing right of the camera*/
	glm::vec3 rightDirection;
	/*Constructor. Default values are: cameras position is at the origo, it looks along the positive z axis and it's up is positive y*/
	Camera(glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), glm::vec3 up = glm::vec3(0.0, 1.0, 0.0), glm::vec3 dir = glm::vec3(0.0, 0.0, -1.0));
	/*Moves the camera by leap*/
	void Move(glm::vec3 leap);
	/*Sets this position to the given location*/
	void SetPosition(glm::vec3 location);
	/*Yaws the camera around the given target*/
	void Yaw(float rotation, glm::vec3& targetPos);
	/*Pitches the camera around the given object*/
	void Pitch(float rotation, glm::vec3& targetPos);
	/*Zooms in a given amount*/
	void ZoomIn(float amount);
	/*Zooms out a given amount*/
	void ZoomOut(float amount);
	/*returns current yaw*/
	float GetYaw();

	/*returns current pitch*/
	float GetPitch();
	/*returns the current view matrix*/
	glm::mat4 GetCurrentView();
};

