#version 430
#define PI 3.141592
layout (location = 0) in vec3 pos;
layout(location = 2) in vec3 nrm;
layout (location = 3) in vec2 uv;
uniform mat4 mvp;
uniform mat4 model;
uniform float time;
uniform bool mode;
out vec2 fragUV;
out vec3 fragNrm;
mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}
void main(){
	vec3 newPos = pos;
	mat3 nrmMatrix;
	nrmMatrix = transpose(inverse(mat3(model)));
	if (mode)   {
		newPos.zy = rotate( PI * 0.25 * sin(time)) * newPos.zy;
	}
	gl_Position = mvp * vec4(newPos, 1.0);
	fragUV = vec2(uv.x, uv.y);
	fragNrm = normalize(nrm);
}