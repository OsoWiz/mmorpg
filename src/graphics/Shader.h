#pragma once
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

class Shader
{
private:
	const std::string v_path;
	const std::string f_path;
public:
	unsigned int id;

	Shader(const std::string& VertexPath, const std::string& FragmentPath);
	/*Uses this shader*/
	void Use();
	/*Unuses this*/
	void Unuse();
	//Utility functions for uniforms
	/*Sets up a 4x4 matrix uniform for the current bound shader. (Which hopefully is this one)*/
	void SetMat4(const std::string& name, glm::mat4& matrix);
	/*Sets up a 4 dimensional float vector for the current bound shader*/
	void SetVec4(const std::string& name, glm::vec4& vector);
	/*Sets up an unsigned integer. Mostly for texture locations*/
	void SetUnsint(const std::string& name, unsigned int i);
	/*Sets up an  integer.Mostly for texture locations*/
	void SetInt(const std::string& name, int i);

};

