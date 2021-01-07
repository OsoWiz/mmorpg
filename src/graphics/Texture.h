#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <stb_image.h>
/*Texture class*/
class Texture
{
private:
	unsigned int id;
	int height_;
	int width_;
	int channels;
public:
	/*Default constructor creates a 2D texture from the given image(requires width and trhe height as ints). It supposes that the image is indeed valid. Default parameters are linear mipmap behaviour and repeating the image if out of bounds*/
	Texture(unsigned char* image,int width,int height,int nrofChannels);
	/*Texture destructor */
	~Texture();
	/*Get the id of this texture*/
	unsigned int GetId();
	/*Returns the image width*/
	int Width();
	/*Returns the image height*/
	int Height();
	
	/*Binds THIS texture*/
	void Bind();
	/*Unbinds texture so no modifications are possible. (BTW unbinding means there is no texture bound I suppose)*/
	void Unbind();
	/*Activates the given texture unit (does not bind this currently)*/
	void Activate(const int& slot);
	/*Deactivates something? I don't even know anymore*/
	void Deactivate();

};

