#version 430
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 3) in vec2 uv;


uniform mat4 mvp;
uniform mat4 model;
uniform float time;
out vec2 fragUV;

void main(){
	vec3 newPos = pos;
	float deg = time;
	
	newPos.z = (color.r + color.g + color.b) / 10.0;
	
	gl_Position = mvp * vec4(newPos, 1.0);
	
	fragUV = vec2(uv.x , 1.0 - uv.y );
}