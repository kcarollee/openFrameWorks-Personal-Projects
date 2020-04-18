#version 430
layout(location = 0) in vec3 pos;
layout(location = 3) in vec2 uv;
uniform mat4 mvp;
uniform bool webcamMode;
out vec2 fragUV;
void main(){
	gl_Position = mvp * vec4(pos, 1.0);
	if (webcamMode) fragUV = vec2(uv.x, uv.y); // webcam
	else fragUV = vec2(1.0 - uv.x, uv.y); // video
}