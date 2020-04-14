#version 430
#define PI 3.141592
#define MAX_STEPS 100
#define SURFACE_DIST 0.001
#define MAX_DIST 20.
#define MAX_OBJ_NUM 100
uniform float time;
uniform sampler2D tex;
uniform float smoothUnion, gap, width, soundVal;
in vec2 fragUV;
out vec4 outColor;


// math util
float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
    return mix(d2, d1, h) - k * h * (1.0 - h); 
}

float getMinimum(float arr[MAX_OBJ_NUM], int size){
	float minimum = arr[0];
	for (int i = 0; i < size - 1; i++){
		minimum = opSmoothUnion(minimum, arr[i+1], soundVal * 0.75);
	}
	return minimum;
}

mat2 Rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}



// shapes
float Box(vec3 p, vec3 pos, vec3 s){
	return  length(max(abs(p - pos) - s, 0.0));
}
// define scenes
float GetDistanceFromScene(vec3 p){
	float shapeArr[MAX_OBJ_NUM];
	vec3 rp = mod(p, gap * 2.0) - gap; // rect p ray modded
	vec3 sp = mod(p, gap * 2.0) - gap; // sphere p ray modded
	int index = 0;
	shapeArr[index++] = Box(rp, vec3(0), vec3(gap, width , width));
	shapeArr[index++] = Box(rp, vec3(0), vec3(width, gap, width));
	shapeArr[index++] = Box(rp, vec3(0), vec3(width, width, gap));
	float final = getMinimum(shapeArr, index);
	return final;
}

// ray march
float RayMarch(vec3 rayOrig, vec3 rayDir){
	float dist = 0;
	for (int i = 0; i < MAX_STEPS; i++){
		vec3 p = rayOrig + dist * rayDir; // new starting point
		float distScene = GetDistanceFromScene(p);
		dist += distScene;
		if (distScene < SURFACE_DIST || dist > MAX_DIST) break;
	}
	return dist;
}

// normals and lights
vec3 Normal(vec3 p){
	float a = 0.001;
	float dist = GetDistanceFromScene(p);
	vec3 norm = vec3(
		dist - GetDistanceFromScene(p - vec3(a, 0, 0)),
		dist - GetDistanceFromScene(p - vec3(0, a, 0)),
		dist - GetDistanceFromScene(p - vec3(0, 0, a))
	); 
	return normalize(norm);
}

vec3 DiffuseLight(vec3 p, vec3 rayDir, float d){
	vec4 side = texture(tex, p.xz - 0.5);
	vec4 top = texture(tex, max(p.xy, p.xz) + 0.5 + time);
	vec3 normal = Normal(p);
	
	vec3 lightCol = vec3(0.80, 0.59, 0.80);
	vec3 lightPos = vec3(0, 0, time);
	vec3 lightDir = normalize(lightPos - p);
	float difLight = clamp(dot(normal, lightDir), 0, 1) / clamp(pow(d, 0.5), 0.75, MAX_DIST); // clamp the value between 0 and 1
	float shadowVal = RayMarch(p + normal * SURFACE_DIST, lightDir);
	if (shadowVal < length(lightPos - p)) difLight = 0.0;
	if (difLight == 0) return vec3(0.79, 1.00, 0.44)/ clamp(pow(d, 0.5), 0.75, MAX_DIST);
	
	vec3 lightCol2 = vec3(0.59, 0.80, 0.59);
	vec3 lightPos2 = vec3(sin(time), cos(time), time);
	vec3 lightDir2 = normalize(lightPos2 - p);
	float difLight2 = clamp(dot(normal, lightDir2), 0, 1) / clamp(pow(d, 0.5), 0.75, MAX_DIST); // clamp the value between 0 and 1
	float shadowVal2 = RayMarch(p + normal * SURFACE_DIST, lightDir2);
	if (shadowVal2 < length(lightPos2 - p)) difLight2 = 0.0;

	return (lightCol * difLight + lightCol2 * difLight2);
}



void main(){
	vec2 uv = fragUV - 0.5; // place uv(0, 0) at zero
	vec3 col = vec3(0);
	vec3 texCol = texture(tex, fragUV).rgb;
	
	// camera
	vec3 rayOrigin = vec3(0, 0, time); // keep the light position in mind too
	//rayOrigin.xy *= Rotate(time);
	vec3 rayDir = normalize(vec3(uv.x, uv.y, 1));
	rayDir.xz *= Rotate(time / 5.0);
	rayDir.xy *= Rotate(time / 5.0);
	float d = RayMarch(rayOrigin, rayDir);
	vec3 p = rayOrigin + rayDir * d;
	vec3 diffLight = DiffuseLight(p, rayDir, d);
	col = vec3(diffLight);
	outColor = vec4(col, 1.0);
}