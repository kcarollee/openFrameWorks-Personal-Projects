#version 430
struct Camera{
	vec3 position;
	vec3 dir;
};
in vec2 fragUV;
in vec3 fragNrm;
out vec4 outColor;
uniform float time;
uniform sampler2D fboTex;
uniform Camera camData;

void main(){
	
	vec4 fboTex = texture(fboTex, fragUV);
	
	float val = dot(fragNrm, -camData.dir);
	if (val == 0) val = 0.5;
	fboTex.rgb = val * fboTex.rgb;
	
	outColor = fboTex;
	
}