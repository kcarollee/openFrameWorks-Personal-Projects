#version 430
uniform sampler2D fboTex;
uniform float time;
uniform int mode;

in vec2 fragUV;
out vec4 outColor;
void main(){
	outColor = texture(fboTex, fragUV);
	if (mode % 2 == 0){
		if (outColor.r != 0) outColor = vec4(vec3(tan(tan(outColor.r + outColor.b + time))), 1.0);
	}

	else if (mode % 2 == 1){
		int radius = 10;
		ivec2 pixel = ivec2(gl_FragCoord.xy);
		if (texelFetchOffset(fboTex, pixel, 0, ivec2(-1, 0)).r != 0){
			outColor.r = texelFetchOffset(fboTex, pixel, 0, ivec2(-1, 0)).r ;
		}
	}
}