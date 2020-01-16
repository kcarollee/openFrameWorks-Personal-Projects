#version 410

in vec2 fragUV;
out vec4 outColor;
uniform float time;
uniform float rcThreshold;
mat2 rotate(float deg){
	return mat2(cos(deg), -sin(deg), sin(deg), cos(deg));
}

float circles(vec2 center, vec2 uv){
	return abs(sin(length(center - uv) * 50.0 + time * 5.0));
}

void main(){
	vec2 newFragUV = fragUV;	
	outColor = vec4(vec3(0.0), 1.0);
	outColor += circles(vec2(0.5), newFragUV);
	if(outColor.r  >= rcThreshold) discard;
}