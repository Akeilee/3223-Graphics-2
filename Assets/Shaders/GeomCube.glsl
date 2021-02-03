//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 330 core

layout(triangles) in;
layout(triangle_strip , max_vertices = 95) out;

uniform float time;
uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

in Vertex {
	vec4 colour;
	vec2 texCoord;
} IN[];

out Vertex {
	vec4 colour;
	vec2 texCoord;
} OUT;


void main() {
	mat4 mvp = (projMatrix * viewMatrix * modelMatrix);
	mat4 scale = mat4(1);
	scale[3][3] = 1.0;
	float a = sin(time); //w value for vec4

	for (int i = 0; i < gl_in.length(); ++i) {
	OUT.colour = IN[i].colour;

	float n = 0;

	n = 1; //normal
	gl_Position = mvp* scale * (gl_in[i].gl_Position + vec4(vec3(-1.0, 1.0, 1.0),a)*n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position + vec4(vec3(-1.0, -1.0, 1.0),a)*n*((sin(time)+1)/2) )  ;
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, 1.0),a)*n*((sin(time)+1)/2)  );
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, -1.0, 1.0),a)*n*((sin(time)+1)/2)  );
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();


	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, 1.0),a)*n*((sin(time)+1)/2) );
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position + vec4(vec3(1.0, -1.0, 1.0),a)*n*((sin(time)+1)/2)  );
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, -1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();


	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, -1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, 1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, -1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();


	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, 1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, -1.0, -1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, 1.0, 1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, -1.0, 1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();


	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, 1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, 1.0, -1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, 1.0, 1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, 1.0, -1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();

	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, -1.0, 1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(1,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(-1.0, -1.0, -1.0),a)*n*((sin(time)+1)/2)  ) ;
	OUT.texCoord = vec2(0,1);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, -1.0, 1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(1,0);
	EmitVertex();
	gl_Position = mvp* scale * (gl_in[i].gl_Position  + vec4(vec3(1.0, -1.0, -1.0),a) *n*((sin(time)+1)/2) ) ;
	OUT.texCoord = vec2(0,0);
	EmitVertex();
	EndPrimitive();


	}

}










/*
vec4 explode(vec4 position, vec3 normal) { 
    vec3 direction = normal * ((sin(time) + 1.0) / 2) * 2; 
    return position + vec4(direction, 1);
}

vec3 GetNormal() {
	vec3 a = vec3(gl_in[0].gl_Position) + vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) + vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b)); 
}

void main() {
	vec3 normal = GetNormal();
    gl_Position = explode(gl_in[0].gl_Position, normal);
    OUT.texCoord = IN[0].texCoord;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    OUT.texCoord = IN[0].texCoord;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    OUT.texCoord = IN[0].texCoord;
    EmitVertex();
    EndPrimitive();
}*/








