//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

# version 400

layout(triangles, equal_spacing, ccw) in;

uniform sampler2D heightMap;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time;

in Vertex { // Sent from the TCS
vec2 texCoord;
} IN[]; // Equal to TCS layout size

out Vertex { // Each TES works on a single vertex
vec2 texCoord;
} OUT;

//quads only - not used in this
vec3 QuadMixVec3 ( vec3 a, vec3 b, vec3 c, vec3 d) {
vec3 p0 = mix (a,c, gl_TessCoord.x);
vec3 p1 = mix (b,d, gl_TessCoord.x);
return mix (p0 ,p1 , gl_TessCoord.y);
}
//quads only - not used in this
vec2 QuadMixVec2( vec2 a, vec2 b, vec2 c, vec2 d) {
vec2 p0 = mix (a,c, gl_TessCoord.x);
vec2 p1 = mix (b,d, gl_TessCoord.x);
return mix (p0 ,p1 , gl_TessCoord.y);
}

void main() {
//vec3 combinedPos = QuadMixVec3 (gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz, gl_in[3].gl_Position.xyz);
//OUT.texCoord = QuadMixVec2 (IN[0].texCoord, IN[1].texCoord, IN[2].texCoord, IN[3].texCoord);

vec3 p0 = gl_TessCoord.x * gl_in[0].gl_Position.xyz;
vec3 p1 = gl_TessCoord.y * gl_in[1].gl_Position.xyz;
vec3 p2 = gl_TessCoord.z * gl_in[2].gl_Position.xyz;

vec2 q0 = gl_TessCoord.x *IN[0].texCoord;
vec2 q1 = gl_TessCoord.y *IN[1].texCoord;
vec2 q2 = gl_TessCoord.z *IN[2].texCoord;

vec3 combinedPos = p0+p1+p2;
OUT.texCoord = q0+q1+q2; 

vec4 worldPos = modelMatrix * vec4(combinedPos, 1);
float height = texture(heightMap, OUT.texCoord).x;
worldPos.y -= height*4;
//worldPos.x -= height*5.5 + tan(time); //changes angle (-ve flips it)
worldPos.x -= height*5.5; //changes angle (-ve flips it)
//worldPos.z /= tan(time/2);
gl_Position = projMatrix * viewMatrix * worldPos;
}