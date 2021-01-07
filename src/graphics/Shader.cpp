#include "Shader.h"

Shader::Shader(const std::string& VertexPath, const std::string& FragmentPath):v_path(VertexPath),f_path(FragmentPath)
{
	//Strings to contain the src codes
	std::string vertexCode;
	std::string fragmentCode;
	//Inputfilestreams for each shader type
	std::ifstream ifv;
	std::ifstream iff;

	try
	{
		//Try to open the files
		ifv.open(VertexPath);
		iff.open(FragmentPath);
		//Create stringstreams to read into
		std::stringstream vShaderStr, fShaderStr;
		//Read the whole file to the stream
		vShaderStr << ifv.rdbuf();
		fShaderStr << iff.rdbuf();
		//close the files
		ifv.close();
		iff.close();
		//Convert the strstream to string
		vertexCode = vShaderStr.str();
		fragmentCode = fShaderStr.str();
		//quick debug:
		//std::cout << "Code to compile: \n" << std::endl;
		//std::cout << vertexCode << std::endl;

		//std::cout << fragmentCode << std::endl;

	}
	catch(std::ifstream::failure e)
	{
		std::cout << "Error loading shader file." << std::endl;
	}
	//Change original strings to nullterminated strings
	const char* vertexString = vertexCode.c_str();
	const char* fragmentString = fragmentCode.c_str();

	//create the ids
	unsigned int vertid, fragid;
	//Success flag and 512 character array(string) for storing the (possible) errormessage
	int succeeded;
	char info[512];

	vertid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertid,1,&vertexString,NULL);
	glCompileShader(vertid);
	//Print compilation errors
	glGetShaderiv(vertid, GL_COMPILE_STATUS, &succeeded);
	//aka if the compilation failed
	if (!succeeded)
	{
		glGetShaderInfoLog(vertid,512,NULL,info);
		std::cout << "Error linking vertexShader: " << info << std::endl;
	}

	fragid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragid, 1, &fragmentString, NULL);
	glCompileShader(fragid);
	//Print compilation errors
	glGetShaderiv(fragid, GL_COMPILE_STATUS, &succeeded);
	//aka if the compilation failed
	if (!succeeded)
	{
		glGetShaderInfoLog(fragid, 512, NULL, info);
		std::cout << "Error linking fragmentShader: " << info << std::endl;
	}
	//Create the complete shaderprogram
	id = glCreateProgram();
	//attach everything
	glAttachShader(id, vertid);
	glAttachShader(id, fragid);
	glLinkProgram(id);
	//Print errors if found
	glGetProgramiv(id, GL_LINK_STATUS, &succeeded);
	//Once again were there errors?
	if (!succeeded)
	{
		glGetProgramInfoLog(id,512,NULL,info);
		std::cout << "Error linking the program: " << info << std::endl;
	}
	//delete the shaderobjects, as they are linked and no longer needed
	glDetachShader(id, vertid);
	glDetachShader(id, fragid);
	glDeleteShader(vertid);
	glDeleteShader(fragid);

}

void Shader::Use()
{
	glUseProgram(id);
}

void Shader::Unuse()
{
	glUseProgram(0);
}

//UTILITY UNIFORM FUNCTIONS UNDER THIS COMMENT PLEASE
void Shader::SetMat4(const std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id,name.c_str()),1,GL_FALSE,&matrix[0][0]);
}

void Shader::SetVec4(const std::string& name, glm::vec4& vector)
{
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &vector[0]);
}

void Shader::SetUnsint(const std::string& name, unsigned int i)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), i);
}

void Shader::SetInt(const std::string& name,  int i)
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), i);
}