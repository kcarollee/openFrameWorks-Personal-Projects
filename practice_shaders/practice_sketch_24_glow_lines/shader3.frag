#version 150
uniform vec2 resolution;
uniform vec2 mouse;
uniform float random;
uniform float radius;
uniform float time;
uniform bool mouseMode;


out vec4 outputColor;
const float PI = 3.1415926535897932384626433832795;

float lightOrb(vec2 st, vec2 orbPos, float intensity){
	return 0.01 / length(st - orbPos) * intensity;
}

void main(void)
{	
	vec2 st = gl_FragCoord.xy / resolution;
	vec2 center;
	if (mouseMode) center = mouse.xy / resolution;
	else center = vec2(0.5);
	vec3 color = vec3(0);	
	const int orbNum = 150;
	float orbArr[orbNum];
	float orbArr2[orbNum];
	float orbArr3[orbNum];

	float intensity = 0.04 + 0.005 * sin(time * 2);
	
	for (int i = 0; i < orbNum; i++){
		orbArr[i] = lightOrb(st, vec2(i * 1.0 /orbNum, 0.5 + 0.2 * sin(i *1.0/orbNum * 4.0 * PI + time) + 
		0.1 * sin(i *1.0/orbNum * 2.0 * PI + time)) + 
		0.05 * sin(i *1.0/orbNum * 14.0 * PI + time), intensity);

		orbArr2[i] = lightOrb(st, vec2(i * 1.0 /orbNum, 0.75 + 0.2 * cos(i *1.0/orbNum * 4.0 * PI + time) + 
		0.1 * cos(i *1.0/orbNum * 2.0 * PI + time)) + 
		0.05 * cos(i *1.0/orbNum * 14.0 * PI + time), intensity);

		orbArr3[i] = lightOrb(st, vec2(i * 1.0 /orbNum, 0.25 + 0.2 * cos(i *1.0/orbNum * 4.0 * PI + time) + 
		0.1 * sin(i *1.0/orbNum * 14.0 * PI + time)) + 
		0.05 * cos(i *1.0/orbNum * 3.0 * PI + time), intensity);

		color += orbArr[i];
		color += orbArr2[i];
		color += orbArr3[i];
	}
	
	outputColor = vec4(color, 1.0);
}