#version 430
#define PI 3.141592
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform mat4 mvp;
uniform float time;
out vec2 fragUV;
void main(){
	vec3 newPos = pos;
	
	gl_Position = mvp * vec4(newPos, 1.0);
	fragUV = vec2(uv.x, uv.y);
	
}