#version 430
uniform vec3 colorVal;
in vec2 fragUV;

out vec4 outColor;

void main(){
	float gap = 0.1;
	if (fragUV.x < gap || fragUV.x > 1.0 - gap || 
	fragUV.y < gap || fragUV.y > 1.0 - gap) outColor = vec4(colorVal, 1.0);

	else discard;
}