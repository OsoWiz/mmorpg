#include "Mesh.h"

	Mesh::Mesh(const std::vector<Vertex>& verts, glm::vec3 pos, glm::vec3 relPos) :vertices(verts),nrofVertices(verts.size()),position(pos),rotation(glm::vec3(0.0f)),scale(glm::vec3(1.0f)),relativePosition(relPos)
	{
		UpdateAll();

		//This mesh constructor doesn't initialize IBO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		VBO = new VertexBuffer(vertices);
		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex texture coords
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));
		// vertex normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		//Note: YOU DON'T NEED TO UNBIND VBO's. UNBINDING VAO IS ENOUGH
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		for (auto iter = texturelist.begin(); iter != texturelist.end(); iter++)
		{
			delete(*iter);
		}
		glDeleteVertexArrays(1, &this->VAO);
		VBO->~VertexBuffer();
	}

	bool Mesh::addTexture(const std::string& texturefilepath)
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, nchannels;
		unsigned char* image = stbi_load(texturefilepath.c_str(), &width, &height, &nchannels, 0);

		if (image) {
			Texture* tex = new Texture(image,width,height,nchannels);
			
			texturelist.push_back(tex);
			stbi_image_free(image);
			stbi_set_flip_vertically_on_load(false);
			return true;
		}
		else {
			stbi_image_free(image);
			stbi_set_flip_vertically_on_load(false);
			return false;
		}
	}

	void Mesh::Draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view)
	{
		//Literally the first thing you should do. Activate the shader program you are about to use. 
		//This might get moved to the models location, as we want the same shader to draw each of the objects in the model.
		shader.Use();
		UpdateAll();
		glm::mat4 model = this->GetDrawMatrix(projection, view);
		shader.SetMat4("model",model);

		for (unsigned int i = 0; i < texturelist.size(); i++)
		{
			texturelist[0]->Activate(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number 
			std::string number;
			std::string name = "texture";
			
				number = std::to_string(i);

			shader.SetUnsint((name + number), i);
			glBindTexture(GL_TEXTURE_2D, texturelist[i]->GetId());
		}
		//This was in some example code
		//glActiveTexture(GL_TEXTURE0);

		// draw mesh first bind this vao so it uses the vbo of this mesh
		glBindVertexArray(VAO);
		
		
	
			glDrawArrays(GL_TRIANGLES, 0, unsigned int(nrofVertices) );
		//Unbind stuff
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
		shader.Unuse();

	}

	


	size_t Mesh::GetVertices()
	{
		return nrofVertices;
	}
	glm::mat4 Mesh::GetDrawMatrix(const glm::mat4& projection, const glm::mat4& view)
	{
		return projection * view * this->meshMatrix;
	}

	void Mesh::SetPosition(glm::vec3 pos) {
		this->position = pos;
		UpdatePosition();
	}
	void Mesh::SetRelativePosition(glm::vec3 pos) {
		this->relativePosition = pos;
		UpdatePosition();
	}
	void Mesh::SetRotation(glm::vec3 rotationToDo) {
		this->rotation = rotationToDo;
		UpdateRotation();
	}
	void Mesh::SetScaling(glm::vec3 additionalScale) {
		this->scale = additionalScale;
		UpdateScaling();
	}

	void Mesh::Move(glm::vec3 leap) {
		this->position += leap;
		UpdatePosition();
	}
	void Mesh::Rotate(glm::vec3 rotationToDo) {
		this->rotation += rotationToDo;
		UpdateRotation();
	}
	void Mesh::RotateRelative(glm::vec3 rotationToDo,glm::vec3 origin) {
		this->rotation += rotationToDo;
		UpdateRotation();
		this->position = this->position - origin;
		this->position = glm::rotate(glm::mat4(1.0f),glm::radians(rotationToDo.x),glm::vec3(1.0,0.0,0.0) ) * glm::vec4(this->position, 1);
		this->position = glm::rotate(glm::mat4(1.0f), glm::radians(rotationToDo.y), glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(this->position, 1);
		this->position = glm::rotate(glm::mat4(1.0f), glm::radians(rotationToDo.z), glm::vec3(0.0, 0.0, 1.0)) * glm::vec4(this->position, 1);
		this->position = this->position + origin;
		UpdatePosition();
	}
	void Mesh::SetRotationRelative(glm::vec3 rotationToDo, glm::vec3 origin) {
		this->rotation = rotationToDo;
		UpdateRotation();
		this->position = this->position - origin;
		this->position = glm::rotate(glm::mat4(1.0f), glm::radians(rotationToDo.x), glm::vec3(1.0, 0.0, 0.0)) * glm::vec4(this->position, 1);
		this->position = glm::rotate(glm::mat4(1.0f), glm::radians(rotationToDo.y), glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(this->position, 1);
		this->position = glm::rotate(glm::mat4(1.0f), glm::radians(rotationToDo.z), glm::vec3(0.0, 0.0, 1.0)) * glm::vec4(this->position, 1);
		this->position = this->position + origin;
		UpdatePosition();
	}

	void Mesh::Scale(glm::vec3 additionalScale) {
		this->scale += additionalScale;
		UpdateScaling();
	}
	void Mesh::UpdatePosition() {
		this->positionMatrix = glm::translate(glm::mat4(1.0f),this->position+this->relativePosition);
	}

	void Mesh::UpdateRotation() {
		this->rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
		this->rotationMatrix = glm::rotate(this->rotationMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
		this->rotationMatrix = glm::rotate(this->rotationMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	}
	void Mesh::UpdateScaling() {
		this->scaleMatrix = glm::scale(glm::mat4(1.0f), this->scale);
	}

	void Mesh::UpdateAll() {
		UpdateRotation();
		UpdatePosition();
		UpdateScaling();
		this->meshMatrix = this->positionMatrix * this->rotationMatrix * this->scaleMatrix;
	}