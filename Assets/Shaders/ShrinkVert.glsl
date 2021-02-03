//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4 (1.0f);
uniform mat4 projMatrix = mat4 (1.0f);

uniform float time;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;


void main (void)
{
	//float mod = acos(time/3); //shrink forever
	
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	
	//float mod = (cos(time),sin(time));
	float mod = (sin(time));
	mat4 scale = mat4(1.0);
	scale = mat4(mod);
	scale[3][3] = 1.0; //all diagonals are 1
	gl_Position = mvp * scale * vec4(position, 1.0);

	OUT.texCoord = texCoord;
	OUT.colour = vec4(1,1,1,1);
	//OUT.colour = colour;
	
}