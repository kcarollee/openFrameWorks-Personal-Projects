#version 150
uniform vec2 resolution;
uniform sampler2D tex;
out vec4 outCol;


void main(void)
{	
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	uv.y = 1.0 - uv.y;
	vec3 texCol = texture2D(tex, uv).rgb;
	vec3 col = vec3(.0);
	float d = 3.0;
	float i = 2.0;
	if (col.r < 0.001){
	vec2 uvr =  vec2(gl_FragCoord.x - d,  gl_FragCoord.y) / resolution.xy;
	uvr.y = 1.0 - uvr.y;
	col.r += texture2D(tex, uvr).r * i;
	}
	if (col.b < 0.001){
	vec2 uvb = vec2(gl_FragCoord.x,  gl_FragCoord.y + d) / resolution.xy;
	uvb.y = 1.0 - uvb.y;
	col.b += texture2D(tex, uvb).b * i;
	}
	if (col.g < 0.001){
	vec2 uvg =  vec2(gl_FragCoord.x - d,  gl_FragCoord.y + d) / resolution.xy;
	uvg.y = 1.0 - uvg.y;
	col.g += texture2D(tex, uvg).g * i;
	}
	outCol = vec4(col, 1.0);
}