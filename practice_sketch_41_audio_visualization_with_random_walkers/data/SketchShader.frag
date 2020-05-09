#version 430
uniform sampler2D tex;
in vec2 fragUV;
out vec4 outColor;

vec4 bloom(float d, float div){
	vec2 uv = fragUV;
	ivec2 pix = ivec2(gl_FragCoord.xy);
	vec4 bloom;
	if (texelFetchOffset(tex, pix, 0, ivec2(0, 0)).r < 1.0){
		vec4 sum = vec4(0);
		while (d >= 0){
			//texelFetchOffset(tex, pix, 0, ivec2(0, 0)).rgb = vec3(1.0);
			sum += texture(tex, uv + vec2(0, d) * div * d);
			sum += texture(tex, uv + vec2(0, -d) * div * d);
			sum += texture(tex, uv + vec2(d, 0) * div * d);
			sum += texture(tex, uv + vec2(d, d) * div * d);
			sum += texture(tex, uv + vec2(d, -d) * div * d);
			sum += texture(tex, uv + vec2(-d, 0) * div * d);
			sum += texture(tex, uv + vec2(-d, d) * div * d);
			sum += texture(tex, uv + vec2(-d, -d) * div * d);
			d--;
		}
		return bloom = vec4(vec3(sum / 24.0), 1.0);
	}
}

void main(){
	outColor = bloom(3.0, 1.0 / 1000.0);
}