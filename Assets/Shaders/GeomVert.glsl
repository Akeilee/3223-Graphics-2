//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

void main(void)
{
	gl_Position		= vec4(position, 1.0);

	OUT.texCoord	= texCoord;
	OUT.colour = vec4(1,1,1,1);
}