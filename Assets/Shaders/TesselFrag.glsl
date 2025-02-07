//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core
uniform sampler2D heightMap;

in Vertex{
vec2 texCoord;
} IN;

out vec4 fragColor;

void main (void) {
fragColor = texture(heightMap, IN.texCoord);
}