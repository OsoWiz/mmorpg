#version 400 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texPos;

out vec2 texturecoord;

uniform mat4 model;

void main()
{
texturecoord = texPos;
gl_Position = model*vec4(pos,1.0);

}