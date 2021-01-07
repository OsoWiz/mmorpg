#version 400 core

out vec4 FragmentColor;

in vec2 texturecoord;

uniform int side;

uniform sampler2D blendmap;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{

vec4 blendMapColor = texture(blendmap,texturecoord);
float backTextureAmount = 1-(blendMapColor.r+blendMapColor.g+blendMapColor.b);
vec2 tileCoords = texturecoord*side;
vec4 blackColor = texture(texture1,tileCoords)*backTextureAmount;
vec4 redColor = texture(texture2,tileCoords)*blendMapColor.r;
vec4 greenColor = texture(texture3,tileCoords)*blendMapColor.g;
vec4 blueColor = texture(texture4,tileCoords)*blendMapColor.b;

vec4 totalColor = blackColor+redColor+greenColor+blueColor;

FragmentColor = totalColor;

}
