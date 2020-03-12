#version 430
layout(location = 0) in vec3 pos;
layout(location = 3) in vec2 uv;
uniform mat4 mvp;
uniform float time;
uniform int mode;
out vec2 fragUV;


mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}
void main(){
	vec3 newPos = pos;

	if (mode % 5 == 0) newPos.z = 0.02 * sin(time * 10 + newPos.x * 10);
	else if (mode % 5 == 2) newPos.z = 0.02 * sin(time * 10 + newPos.y * 10);
	else if (mode % 5 == 3) {
		float inity = newPos.y;
		float initx = newPos.x;
		newPos.x = initx + 0.05 * sin(time + newPos.y * 10);
		newPos.y = inity + 0.05 * cos(time + newPos.x * 10);
	}
	else if (mode % 5 == 4) {
		float inity = newPos.y;
		float initx = newPos.x;
		//newPos.x = initx + 0.05 * tan(time + newPos.y * 10);
		newPos.y = inity + 0.1 * tan(time * 2.0 + newPos.x * 2000);
	}
	gl_Position = mvp * vec4(newPos, 1.0);
	fragUV = vec2(uv.x, 1.0 -  uv.y);
}