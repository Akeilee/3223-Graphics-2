//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core

uniform sampler2D mainTex; // old texture , on Tex Unit 0
uniform sampler2D secondTex; // new texture , on Tex Unit 1

uniform float time;

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;


void main (void){

	//if texture size is 0 then use in.colour
	if(textureSize(mainTex,1).x <1.0f){
	fragColor = IN.colour;
	}

	vec4 cleanTex = texture( mainTex , IN.texCoord );
	vec4 destroyTex = texture( secondTex , IN.texCoord );
	
	//changing alpha over time
	cleanTex.a -=time;
	destroyTex.a =+time;

	//re-adjusting colours
	cleanTex.rbg -=0.2;
	destroyTex.r +=0.3;
	destroyTex.g +=0.2;
	destroyTex.b +=0.11;

	float change = (sin(time));

	fragColor = (cleanTex * change) + (destroyTex);

}