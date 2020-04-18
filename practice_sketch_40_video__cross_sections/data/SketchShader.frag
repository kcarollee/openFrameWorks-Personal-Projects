#version 430
uniform sampler2D sketchTex;
uniform sampler2D webcamGrayDiffTex;
in vec2 fragUV;
out vec4 outColor;
void main(){
	vec3 outCol = texture(sketchTex, fragUV).rgb;
	//outCol = vec3((outCol.r + outCol.g + outCol.b) / 3.0);
	outColor = vec4(outCol, 1.0);
}