#pragma once
#include <GL/glew.h>

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
#include "stb_image.h"
#include "Vertex.h"
/*Loads 3d models and skyboximages. The model loading functionality is for the most part (I think almost fully) created originally by a github user headturna. So credits to him on this one.*/
class ObjectLoader
{
public:
	std::vector<Vertex> loadOBJ(const char* file_name);
	std::vector<unsigned char*> loadCubemap(std::vector<std::string> filepaths,int&width,int&height,int&channels);
};

