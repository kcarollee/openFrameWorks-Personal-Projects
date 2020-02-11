#version 430

uniform float time;
uniform vec3 campos;
uniform vec4 colorOffset;
in vec2 fragUV;
in vec3 fragNrm;
out vec4 outColor;

void main(){	
	float lightAmount = 1.0 - dot(fragNrm, campos);
	vec3 rimlightColor;
	rimlightColor = vec3(mix(0.0, 1.0, colorOffset.x), 
	mix(0.0, 1.0, colorOffset.y), 
	mix(0.0, 1.0, colorOffset.z));
	outColor = vec4(rimlightColor * lightAmount, colorOffset.a);
	if (outColor.r < 0.01) discard;

}