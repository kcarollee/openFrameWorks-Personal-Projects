#version 430
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform mat4 mvp;
uniform mat4 model;
uniform float time;
out vec2 fragCoord;



void main(){
	vec3 newPos = pos;
	newPos = mat3(model) * newPos;
	//newPos.xz = rotate(time) * newPos.xz;
	gl_Position = mvp * vec4(newPos, 1.0);
	fragCoord = vec2(1.0 - uv.x, 1.0 - uv.y);
}