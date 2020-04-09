#version 430
#define PI 3.141592
#define MAX_STEPS 100
#define SURFACE_DIST 0.01
#define MAX_DIST 100.
#define MAX_OBJ_NUM 100
uniform float time;
uniform sampler2D tex;
uniform float s0, s1, s2;
uniform float cx, cy, cz, smoothUnion;
uniform int dispMode;
in vec2 fragUV;
out vec4 outColor;

// works in progress
float LineBox(vec3 p, vec3 pos, vec3 s){
	float e = -0.025;
	float x = abs(p.x - pos.x) - s.x;
	float y = abs(p.y - pos.y) - s.y;
	float z = abs(p.z - pos.z) - s.z;
	if ((x < e && y > e &&  z > e) ||
		(x > e && y < e &&  z > e) ||
		(x > e && y > e &&  z < e) ||
		(x > e && y > e &&  z > e)){
		p = abs(p - pos) - s;
		return length(max(p, 0.))+min(max(p.x, max(p.y, p.z)), 0.);;
	}
	else return 100.0;
}

// math util
float opSub(float d1, float d2){
	return max(d1, -d2);
}
float opUnion(float d1, float d2){
	return min(d1, d2);
}
float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h); 
}

float getMinimum(float arr[MAX_OBJ_NUM], int size){
	float minimum = arr[0];
	for (int i = 0; i < size - 1; i++){
		minimum = opUnion(minimum, arr[i+1]);
	}
	return minimum;
}

mat2 Rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}



// shapes
float Box(vec3 p, vec3 pos, vec3 s){
	return length(max(abs(p - pos) - s, 0.0));
}

float XZPlane(vec3 p){
	return p.y;
}

float YZPlane(vec3 p){
	return p.x;
}

float XYPlane(vec3 p){
	return p.z;
}

float ModifiedSphere(vec3 p, vec3 pos, float r){
	float disp = sin(p.x * cx + p.y * cy + p.z * cz  + time * 2.5);
	float dispx = sin(p.x  * cx  + time);
	float dispy = cos(p.y  * cy  + time);
	float dispz = sin(p.z * cz + time);
	vec3 dispVec = vec3(dispx, dispy, dispz);
	if (dispMode == 0) return length(p - pos + disp) - r;
	else return length(p - pos + dispVec) - r;
}



// define scenes
float GetDistanceFromScene(vec3 p){
	float shapeArr[MAX_OBJ_NUM];


	int index = 0;
	float boxWidth = 0.5;
	for (int i = 0; i < 1; i++){
		shapeArr[2 * i] = ModifiedSphere(p, vec3(sin(time), 2.0 - i * boxWidth * 2, 5), 0.75);
		shapeArr[2 * i + 1] = ModifiedSphere(p, vec3(sin(time + PI), 2.0 - i * boxWidth * 2, 5), 0.75);
		index += 2;
	}
		
	shapeArr[index] = XZPlane(p);
	shapeArr[index + 1] = YZPlane(p + 1.5);
	shapeArr[index + 2] = -YZPlane(p - 1.5);
	shapeArr[index + 3] = XYPlane(p  + 0.5);

	float final = getMinimum(shapeArr, index);
	float k = 0.5;
	final = opSmoothUnion(final, shapeArr[index], smoothUnion);
	final = opSmoothUnion(final, shapeArr[index + 1], smoothUnion);
	final = opSmoothUnion(final, shapeArr[index + 2], smoothUnion);
	final = opSmoothUnion(final, shapeArr[index + 3], smoothUnion);
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
	float a = 0.01;
	float dist = GetDistanceFromScene(p);
	vec3 norm = vec3(
		dist - GetDistanceFromScene(p - vec3(a, 0, 0)),
		dist - GetDistanceFromScene(p - vec3(0, a, 0)),
		dist - GetDistanceFromScene(p - vec3(0, 0, a))
	); 
	return normalize(norm);
}

vec3 DiffuseLight(vec3 p){
	vec3 lightCol = vec3(0.9, 0.5, 0.4);
	vec3 lightPos = vec3(0, 3, 1 + sin(time));
	vec3 lightDir = normalize(lightPos - p);
	vec3 normal = Normal(p);
	float difLight = clamp(dot(normal, lightDir), 0, 1); // clamp the value between 0 and 1
	float shadowVal = RayMarch(p + normal * SURFACE_DIST, lightDir);
	if (shadowVal < length(lightPos - p)) difLight *= 0.0;

	vec3 lightCol2 = vec3(0.4, 0.5, 0.9);
	vec3 lightPos2 = vec3(0, 4, 1 + sin(time + PI / 3.0));
	vec3 lightDir2 = normalize(lightPos2 - p);
	vec3 normal2 = Normal(p);
	float difLight2 = clamp(dot(normal2, lightDir2), 0, 1); // clamp the value between 0 and 1
	float shadowVal2 = RayMarch(p + normal2 * SURFACE_DIST, lightDir2);
	if (shadowVal2 < length(lightPos2 - p)) difLight *= 0.0;

	vec3 lightCol3= vec3(0.5, 0.9, 0.4);
	vec3 lightPos3= vec3(0, 4, 1 + sin(time + 2.0 * PI / 3.0));
	vec3 lightDir3= normalize(lightPos3- p);
	vec3 normal3= Normal(p);
	float difLight3= clamp(dot(normal3, lightDir3), 0, 1); // clamp the value between 0 and 1
	float shadowVal3= RayMarch(p + normal3* SURFACE_DIST, lightDir3);
	if (shadowVal3< length(lightPos3- p)) difLight *= 0.0;
	
	
	return lightCol * difLight + lightCol2 * difLight2 + lightCol3 * difLight3;
}



void main(){
	vec2 uv = fragUV - 0.5; // place uv(0, 0) at zero
	vec3 col = vec3(0);
	vec3 texCol = texture(tex, fragUV).rgb;
	
	// camera
	vec3 rayOrigin = vec3(0, 1.5, 0);
	vec3 rayDir = normalize(vec3(uv.x, uv.y, 1));
	
	float d = RayMarch(rayOrigin, rayDir);
	vec3 p = rayOrigin + rayDir * d;
	vec3 diffLight = DiffuseLight(p);
	col = vec3(diffLight);
	outColor = vec4(col, 1.0);
}