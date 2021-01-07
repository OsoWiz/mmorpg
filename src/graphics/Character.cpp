#include "Character.h"


Character::Character(Mesh* baseModel,  const std::string type, glm::vec3 pos, const int id):characterModel(baseModel),id(id),type(type),position(pos), rotation(glm::vec3(0.0, 0.0, 0.0)), scaling(glm::vec3(1.0f))
{
	this->helmet = nullptr;
}


Character::~Character()
{
	this->characterModel->~Mesh();
	if (this->helmet != nullptr) this->helmet->~Mesh();
}


bool Character::AddHelmet(Mesh* helmet)
{
	if (helmet == nullptr) {
		this->helmet = helmet;
		return true;
	}
	else return false;
}

bool Character::HasHelmet()
{
	return this->helmet != nullptr;
}

void Character::EquipHelmet(Mesh* helmet)
{
	this->helmet = helmet;
}

std::string Character::GetType()
{
	return this->type;
}
int Character::GetId()
{
	return this->id;
}

void Character::Move(glm::vec3 leap)
{
	this->position += leap;
	this->characterModel->Move(leap);
	if (this->HasHelmet())this->helmet->Move(leap);
}

void Character::SetPosition(glm::vec3 pos)
{
	this->position = pos;
	this->characterModel->SetPosition(pos);
	if (this->HasHelmet()) {
		auto relative = this->helmet->position;
		this->helmet->SetPosition(pos+relative);
	}
}

void Character::Scale(glm::vec3 scaling)
{
	this->characterModel->Scale(scaling);
	if (this->HasHelmet()) this->helmet->Scale(scaling);
}

void Character::SetScaling(glm::vec3 scaling)
{
	this->characterModel->SetScaling(scaling);
	if (this->HasHelmet()) this->helmet->SetScaling(scaling);
}

void Character::Rotate(glm::vec3 rotation)
{
	this->rotation += rotation;
	this->characterModel->Rotate(rotation);
	if (this->HasHelmet()) this->helmet->RotateRelative(rotation,this->position);
}
void Character::SetRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
	this->characterModel->SetRotation(rotation);
	if (this->HasHelmet())this->helmet->SetRotation(rotation);
}

bool Character::AddCharacterTexture(const std::string& filepath)
{
	return this->characterModel->addTexture(filepath);
}

bool Character::AddHelmetTexture(const std::string& filepath)
{
	return this->helmet->addTexture(filepath);
}

void Character::Draw(Shader& shader, glm::mat4 proj, glm::mat4 view)
{
	this->characterModel->Draw(shader, proj, view);
	if(this->HasHelmet())this->helmet->Draw(shader, proj, view);
}