//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core
layout (vertices =3) out; // num vertices in output patch

uniform float tessLevelInner; //fixed size 2
uniform float tessLevelOuter; //fixed size 4
uniform float time;

in Vertex{
vec2 texCoord; // From Vertex Shader
} IN[]; // Equal to size of the draw call vertex count

out Vertex {
vec2 texCoord; // To Evaluation Shader
} OUT[]; // Equal to the size of the layout vertex count

patch out vec4 subColour;

void main () {
float a = 0;
a += time; //gradual change

gl_TessLevelInner[0] = 1;

gl_TessLevelOuter[0] = 1 ;
gl_TessLevelOuter[1] = 1 ;
gl_TessLevelOuter[2] = 1 ;

if (time >1){
gl_TessLevelInner[0] = 1;
gl_TessLevelInner[0] += sin(time/3)*a*1.9;

gl_TessLevelOuter[0] = 1 ;
gl_TessLevelOuter[0] += sin(time/3)*a*1.8;
gl_TessLevelOuter[1] = 1;
gl_TessLevelOuter[1] += sin(time/3)*a*1.3;
gl_TessLevelOuter[2] = 1;
gl_TessLevelOuter[2] += sin(time/3)*a*2.2;
}

OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
barrier();
gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;


}





/*void main () {
gl_TessLevelInner[0] = 18;
gl_TessLevelInner[0] -= sin(time) * 2;

gl_TessLevelOuter[0] = 20 ;
gl_TessLevelOuter[0] -= sin(time) * 2 ;
gl_TessLevelOuter[1] = 10;
gl_TessLevelOuter[1] -= sin(time) * 2;
gl_TessLevelOuter[2] = 20;
gl_TessLevelOuter[2] -= sin(time) * 2;


OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;

barrier();
gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

}*/

