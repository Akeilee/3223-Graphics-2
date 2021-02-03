//tut10
#version 400 core

uniform sampler2D mainTex; // old texture , on Tex Unit 0
uniform sampler2D secondTex; // new texture , on Tex Unit 1

uniform float time; // From the previous tutorial

in Vertex
{
	vec4 colour;
	vec2 texCoord;
} IN;

out vec4 fragColor;

void main (void){
	vec4 smileyColour = texture( mainTex , IN.texCoord );

	if( smileyColour.b > 0.1) {
	
		vec4 tempColour = IN.colour;
		tempColour.a = 0;
		
		vec2 tempTex = IN.texCoord;
		tempTex.y += time;

		fragColor = texture(secondTex , tempTex );
		
		
		fragColor.a -= time/5; //disappear
		//appears but need to have alpha blending on linear
		//fragColor.a = tempColour.a;
		//fragColor.a += time/10;
		
	}
	else {
		fragColor = smileyColour;
	}
	
	if(smileyColour.r > 0.2){
		discard;
	}
}