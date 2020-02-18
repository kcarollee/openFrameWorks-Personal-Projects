#version 430
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 tangent;
layout(location = 2) in vec3 nrm;
layout(location = 3) in vec2 uv;

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normal;
uniform float time;
out vec2 fragUV;
out vec2 fragUV2;
out mat3 TBN;
out vec3 fragNrm;
out vec3 fragWorldPos;
void main(){

	float t = time * 0.1;
	float t2 = time * 0.07;
	fragUV = vec2(uv.x   +t, uv.y  ) ;
	fragUV2 = vec2(uv.x  + t2, uv.y -t2);

	fragNrm = normal * nrm;
	fragWorldPos = (model * vec4(pos, 1.0)).xyz;

	vec3 T = normalize(normal * tangent.xyz);
	vec3 B = normalize(normal * cross(tangent.xyz,nrm.xyz));
	vec3 N = normalize(normal * nrm.xyz);
	TBN = mat3(T, B, N);
	gl_Position = mvp * vec4(pos, 1.0);
	
}