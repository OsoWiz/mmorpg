#include "Texture.h"

Texture::Texture(unsigned char* image,int width, int height, int nrofChannels): width_(width),height_(height),channels(nrofChannels)
{
	
	//Maybe call glactivetexture here to activate the right texture unit. But which one is the right one?
	
	//Generate the texture.
	glGenTextures(1, &id);	
		//Bind this as gl  2d texture. So it's in that slot now, as it was the last thing bound.
		glBindTexture(GL_TEXTURE_2D, id);
		//default options on constructor. TODO: additional option functions for this class to change these settings.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//This is what actually generates the texture on the currently bound object.
		if (nrofChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if(nrofChannels ==4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		//Generate mipmap at the current gl texture 2d
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1,&id);
	}


	unsigned int Texture::GetId()
	{
		return id;
	}
	 int Texture::Width()
	{
		return width_;
	}
	 int Texture::Height()
	{
		return height_;
	}


	void Texture::Bind()
	{
	glBindTexture(GL_TEXTURE_2D, id);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Activate(const int& slot)
	{
		glActiveTexture(slot);
		//glBindTexture(GL_TEXTURE_2D, id);
	}
	void Texture::Deactivate()
	{
		glActiveTexture(0);
		//glBindTexture(GL_TEXTURE_2D, id);
	}