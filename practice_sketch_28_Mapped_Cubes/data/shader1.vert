#version 410
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform float time;
uniform vec3 translate;
out vec2 fragUV;

mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}

void main(){
	vec3 newPos = pos;
	newPos.xz = rotate(time) * newPos.xz;
	newPos.yz = -rotate(time) * newPos.yz;
	newPos.xy = rotate(time) * newPos.xy;
	gl_Position = vec4(newPos + translate, 1.0);
	fragUV = uv;
}