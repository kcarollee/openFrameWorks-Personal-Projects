#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 3) in vec2 uv;

out vec2 fragUV;

uniform float time;
uniform mat4 mvp;
uniform mat4 model;
uniform float popOut;


void main(){
	vec3 newPos = pos;
	// use color info from webcamFeed
	float colorVal = (color.r + color.b + color.g) / 3.0;	
	newPos.z = popOut * (colorVal - floor(colorVal)) / 5.0;
	if (newPos.z < 0.05 && newPos.z > -0.05) newPos.z = 0;
	
	// morphing planes
	//newPos.z = 0.1 * sin(cos(pos.x * 10.0 + pos.y * 10.0  + time * 3.0));
	
	gl_Position = mvp *  vec4(newPos, 1.0);
	fragUV = vec2(uv.x, 1.0 - uv.y);
}