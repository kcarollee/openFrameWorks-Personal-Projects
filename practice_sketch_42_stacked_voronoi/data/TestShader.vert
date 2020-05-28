#version 430

layout(location = 0) in vec3 pos;
layout(location = 3) in vec2 uv;
uniform mat4  mvp;
uniform vec3 shapeCenter;
uniform float translateX;
uniform float time;
uniform int translateMode; // 0: sketch 1: ui

out vec2 fragUV;

mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}
void main(){
	vec3 newPos = pos;
	float t = time * 0.5;
	switch(translateMode){
	// sketch
	case 0:
		newPos.xz = rotate(t) * newPos.xz;
		newPos.yz = rotate(t) * newPos.yz;
		newPos.xy = rotate(t) * newPos.xy;
		newPos.x -= 1.4;
		break;
	// ui
	case 1:
		newPos.z -= 1.0;
		newPos.x += 1.0;
		newPos.x /= 2.0;
		break;
	case 2:
		newPos.xz = rotate(t) * newPos.xz;
		newPos.yz = rotate(t) * newPos.yz;
		newPos.xy = rotate(t) * newPos.xy;
		break;
	}	
	gl_Position = mvp * vec4(newPos, 1.0);
	fragUV = vec2(uv.x, 1.0 - uv.y);
}