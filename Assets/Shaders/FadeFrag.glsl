//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core

uniform sampler2D mainTex;

uniform float time;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main (void){

	vec4 main = texture(mainTex , IN.texCoord);
	main.a += sin(time*1.5);

	fragColor = main;

}