#version 410

uniform sampler2D webcamFeed;
uniform float time;
uniform int toggleColor;
in vec2 fragUV;
out vec4 outColor;

void main(){
	if (toggleColor == 1){
		outColor = vec4(vec3(texture(webcamFeed, fragUV).r), 1.0);
		if (outColor.r < 0.4) discard;
		outColor = 2.0 * vec4(0.0,  mix(0, 1, 1 - outColor.r), mix(0, 1, outColor.r), 1.0);
	}
	
	else outColor = vec4(vec3(1.0), 0.6);
}