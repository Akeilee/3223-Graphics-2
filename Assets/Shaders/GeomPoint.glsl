//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 330 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);

uniform float time; 

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
	vec3 worldPos;
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
} IN[];

out Vertex {
	vec3 worldPos;
	vec4 colour;
	vec2 texCoord;
	vec3 normal;
} OUT;


void main() {

	vec3 product = vec3(0,0,0);
	vec3 normDirection = vec3(0,0,0);

	vec3 a = vec3(gl_in[0].gl_Position) + vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) + vec3(gl_in[1].gl_Position);
	
	product = cross(a,b);
	normDirection = normalize(product) * (sin(time)+ 1) * 3; 

	gl_Position = gl_in[0].gl_Position + vec4(normDirection,1);
	OUT.texCoord = vec2(1,0);
	OUT.normal = normalize(a);
	EmitVertex();

	gl_Position = gl_in[1].gl_Position + vec4(normDirection,1);
	OUT.texCoord = vec2(0,1);
	OUT.normal = normalize(b);
	EmitVertex();

	gl_Position = gl_in[2].gl_Position + vec4(normDirection,1);
	OUT.texCoord = vec2(0.5,0.5);
	OUT.normal = normalize(b);
	EmitVertex();

	EndPrimitive();

}