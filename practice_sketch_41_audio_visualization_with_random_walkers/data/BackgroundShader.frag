#version 430
#define TWO_PI 6.28318530718
#define PI 3.14159265359
#define HALF_PI 1.57079632679
#define MAX_OBJ_NUM 1000
uniform vec3 colorVal;
uniform float time;
uniform float bgSoundVal;
in vec2 fragUV;
float getMaximum(float arr[MAX_OBJ_NUM], float size){
	float maximum = arr[0];
	for (int i = 0; i < size - 1; i++){
		maximum = max(maximum, arr[i+1]);
	}
	return maximum;
}
out vec4 outColor;

float circle(float radius, vec2 uv, vec2 pos){
	if (length(uv - pos) < radius) 
	return 1.0 - smoothstep(radius - 0.01, radius + 0.01, 
	sin(length(uv - pos) * (250 + 10 * bgSoundVal) + time * 5.0 + bgSoundVal * 200));
}

float plot(vec2 uv, float pct){
  return  smoothstep( pct-0.01, pct, uv.y) -
          smoothstep( pct, pct+0.01, uv.y);
}

mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}

void main(){
	vec2 uv = fragUV;
	vec3 defaultCol = vec3(uv.x, uv.y, 1.0);
	float pctArr[MAX_OBJ_NUM];
	
	
	
	pctArr[0] = circle(0.2, uv, vec2(0.5));
	uv -= vec2(0.5);
	uv = rotate(time) * uv;
	pctArr[1] = plot(uv, 0.025 * sin(uv.x * (53.0 + 10.0 * bgSoundVal) + time * 10.0) + 0.025 * cos(uv.x *67.0));
	uv = rotate(-time) * uv;

	uv = rotate(time + HALF_PI / 2.0) * uv;
	pctArr[2] = plot(uv, 0.025 * sin(uv.x * (61.0 + 10.0 * bgSoundVal) + time * 10.0) + 0.025 * cos(uv.x *71.0));
	uv = rotate(-time - HALF_PI / 2.0) * uv;

	uv = rotate(time + HALF_PI) * uv;
	pctArr[3] = plot(uv, 0.025 * sin(uv.x * (61.0 + 10.0 * bgSoundVal) + time * 10.0) + 0.025 * cos(uv.x *71.0));
	uv = rotate(-time - HALF_PI) * uv;

	uv = rotate(time + 3.0 * HALF_PI / 2.0) * uv;
	pctArr[4] = plot(uv, 0.025 * sin(uv.x * (59.0 + 10.0 * bgSoundVal) + time * 10.0) + 0.025 * cos(uv.x * 67.0));
	
	defaultCol *= getMaximum(pctArr, 5);
	outColor = vec4(defaultCol, 1.0);
;}