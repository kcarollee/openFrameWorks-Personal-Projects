#version 150
uniform vec2 resolution;
uniform sampler2D currentBuffer;
uniform sampler2D backBuffer;


out vec4 outCol;


void main(void)
{	
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	vec3 col = vec3(.0);
	uv.y = 1.0 - uv.y;
	vec3 cur = texture(currentBuffer, uv).rgb;
	vec3 bb = texture(backBuffer, uv).rgb;
	
	float d = 3.0;
	float div = 1.0 / 200.0;

	vec4 sum = vec4(.0);
	while (d >= 0){
		sum += texture(currentBuffer, uv + vec2(0, d) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(0, -d) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(d, 0) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(d, d) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(d, -d) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(-d, 0) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(-d, d) * pow(div, d));
		sum += texture(currentBuffer, uv + vec2(-d, -d) * pow(div, d));
		d--;
	}
	col += sum.rgb * 0.125;
	col += cur + bb * 0.75;



	outCol = vec4(col, 1.0);
}
