#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 3) in vec2 uv;

out vec2 fragUV;

uniform float time;
uniform mat4 mvp;
uniform mat4 model;
uniform int fragMode;


void main(){
	vec3 newPos = pos;
	// wave
	//newPos.z = 0.1 * sin(newPos.x * 8.0 + time * 3.0)  + 0.1 * cos(newPos.y * 8.0 + time * 3.0);
	// color
	//newPos.z = (color.x + color.y) / 10.0;
	//if (color.b > 0.7) newPos.z = color.b / 10.0;
	if (fragMode == 0){
		newPos.z = 0.05 * sin(newPos.x * 8.0 + time * 3.0)  + 0.05 * cos(newPos.y * 8.0 + time * 3.0);
	}
	gl_Position = mvp *  vec4(newPos, 1.0);
	
	fragUV = vec2(uv.x, 1.0 - uv.y);
}