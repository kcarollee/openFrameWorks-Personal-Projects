#version 410

uniform sampler2D webcamFeed;
uniform float time;
uniform int fragMode;
in vec2 fragUV;
out vec4 outColor;


float movingCircle(vec2 center, vec2 uv, float r){
	return smoothstep(r - 0.02, r + 0.02, length(center - uv));
}
float circles(vec2 center, vec2 uv){
	return abs(sin(length(center - uv) * 200 + time * 10.0));
}

void main(){
	outColor =texture(webcamFeed, fragUV);
	if (fragMode == 0){
		if (outColor.r > 0.5) discard;
		outColor = vec4(vec3(step(0.3, outColor.g)), 1.0);

	}
	else if (fragMode == 1){
		//outColor -= min(movingCircle(vec2(0.5), fragUV, 0.2), 1.0);  //circular hole
		//outColor += circles(vec2(0.0), fragUV);
		//outColor += circles(vec2(0.5), fragUV);
		outColor += circles(vec2(1.0), fragUV);
		if (outColor.r >= 0.8) discard;
		outColor = 1.0 - vec4(vec3(step(0.5, outColor.g)), 1.0);
		outColor.a = 1.0;
	}
	else if (fragMode == 2){
		//outColor -= min(movingCircle(vec2(0.5), fragUV, 0.2), 1.0);  //circular hole
		outColor += circles(vec2(0.0), fragUV);
		//outColor += circles(vec2(0.5), fragUV);
		//outColor += circles(vec2(1.0), fragUV);
		if (outColor.r >= 0.8) discard;
		outColor = 1.0 -  vec4(vec3(step(0.3, outColor.g)), 1.0);
		outColor.a = 1.0;
	}
}