#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texPos;
//layout (location = 2) in vec3 normal;

//layout (location = 0) in vec2 testpos;

out vec2 texCoord;
/*
uniform mat4 proj;
uniform mat4 view;

*/

uniform mat4 model;
void main()
{
texCoord = texPos;
gl_Position = model *vec4(aPos,1);
//gl_Position = vec4(testpos,1,1);
}