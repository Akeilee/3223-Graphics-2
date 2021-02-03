//Name: Jane Lee 120236521
//Purpose: 3223 CW2
//Date: 12/2019

#version 400 core

uniform sampler2D mainTex;

uniform vec3 cameraPos;

uniform vec3 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;
uniform float time;

in Vertex {
vec3 worldPos;
vec2 texCoord;
vec3 normal;
} IN;

out vec4 fragColor;

void main ( void ) {
vec3 incident = normalize(lightPos - IN.worldPos);
vec3 viewDir = normalize(cameraPos - IN.worldPos);
vec3 halfDir = normalize(incident + viewDir);

float dist = length(lightPos - IN.worldPos);
float atten = 1.0 - clamp(dist/lightRadius, 0.0 , 1.0);

float lambert = max(0.0, dot(incident, IN.normal));

float rFactor = max(0.0, dot(halfDir, normalize(IN.normal)));
float sFactor = pow(rFactor, 30.0); //higher power is shinier

vec4 texCol = texture(mainTex, IN.texCoord);
vec3 ambient = texCol.rgb * lightColour * 0.15; //higher is lighter
vec3 diffuse = texCol.rgb * lightColour * lambert * atten;
vec3 specular = lightColour * sFactor * atten;
fragColor = vec4 ( ambient + diffuse + specular ,texCol.a);
}