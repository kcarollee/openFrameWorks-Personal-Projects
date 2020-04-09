#version 430
layout(location = 0) in vec3 pos;
layout(location = 3) in vec2 uv;
uniform mat4 mvp;
out vec2 fragCoord;
void main(){
	gl_Position = mvp * vec4(pos, 1.0);
	fragCoord = uv;
}