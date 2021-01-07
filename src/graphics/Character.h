#pragma once
#include "Mesh.h"
#include "Texture.h"
/*Class that represents a character, npc or another player*/
class Character
{
private:
	Mesh* helmet;
	Mesh* characterModel;
	const std::string type;
	const int id;
	

public:
	/*These were public due to time constraints*/
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaling;

	Character(Mesh* baseModel,const std::string type, glm::vec3 pos = glm::vec3(0.0, 0.5, 0.0), const int id = 0);
	~Character();
	/*Adds a texture for the charactermodel*/
	bool AddCharacterTexture(const std::string& filepath);
	/*Adds a texture for the helmet*/
	bool AddHelmetTexture(const std::string& filepath);
	/*Adds a helmet*/
	bool AddHelmet(Mesh* helmet);
	/*Checks wether one has a helmet*/
	bool HasHelmet();
	/*Returns the type of the character*/
	std::string GetType();
	/*Returns the id*/
	int GetId();
	/*Draws this character*/
	void Draw(Shader& shader, glm::mat4 proj, glm::mat4 view);
	/*Equips a given helmet*/
	void EquipHelmet(Mesh* helmet);
	/*Moves the amount of the given leap*/
	void Move(glm::vec3 leap);
	/*Sets the characters position to the given one*/
	void SetPosition(glm::vec3 pos);
	/*Scales this character*/
	void Scale(glm::vec3 scaling);
	/*Sets the scaling of this character*/
	void SetScaling(glm::vec3 scaling);
	/*Rotates this character*/
	void Rotate(glm::vec3 rotation);
	/*Sets the rotation of this character*/
	void SetRotation(glm::vec3 rotation);

};

