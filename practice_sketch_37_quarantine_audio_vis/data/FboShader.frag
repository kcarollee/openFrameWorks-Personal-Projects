#version 430
uniform sampler2D fboTex;
uniform float time;
in vec2 fragCoord;
out vec4 outColor;


void main(){
vec2 uv = fragCoord;
	outColor = texture(fboTex, fragCoord);
	ivec2 pix = ivec2(gl_FragCoord.xy);
	float d = 3.0;
	float div = 1.0 / (150.0);
	if (texelFetchOffset(fboTex, pix, 0, ivec2(0, 0)).r < 1.0){
		vec4 sum = vec4(0);
		while (d >= 0){
			//texelFetchOffset(fboTex, pix, 0, ivec2(0, 0)).rgb = vec3(1.0);
			sum += texture(fboTex, uv + vec2(0, d) * div * d);
			sum += texture(fboTex, uv + vec2(0, -d) * div * d);
			sum += texture(fboTex, uv + vec2(d, 0) * div * d);
			sum += texture(fboTex, uv + vec2(d, d) * div * d);
			sum += texture(fboTex, uv + vec2(d, -d) * div * d);
			sum += texture(fboTex, uv + vec2(-d, 0) * div * d);
			sum += texture(fboTex, uv + vec2(-d, d) * div * d);
			sum += texture(fboTex, uv + vec2(-d, -d) * div * d);
			d--;
		}
		outColor = vec4(vec3(sum / 24.0), 1.0);
	}
}