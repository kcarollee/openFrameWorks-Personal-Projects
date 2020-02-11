#version 430

layout(location = 0) in vec3 pos;
layout(location = 2) in vec3 nrm;
layout(location = 3) in vec2 uv;

uniform mat4 mvp;
uniform vec3 campos;

out vec2 fragUV;
out vec3 fragNrm;
out vec3 fragPos;
void main(){
	gl_Position = mvp * vec4(pos, 1.0);
	fragNrm =(nrm).xyz;
	fragUV = uv;
}