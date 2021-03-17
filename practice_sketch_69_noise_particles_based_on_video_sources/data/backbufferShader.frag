#version 150
uniform vec2 resolution;
uniform sampler2D currentBuffer;
uniform sampler2D backBuffer;

out vec4 outCol;


void main(void)
{	
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	vec3 col = vec3(.0);
	vec3 cur = texture(currentBuffer, uv).rgb;
	vec3 bb = texture(backBuffer, uv).rgb;
	float d = 0.8;
	if (cur.r + cur.g + cur.b < 0.001) col = cur + bb;
	else col += cur;
	//col /= 1.0 + d;
	col *= 0.8;
	//if (col.r + col.g + col.r < 0.001) col = vec3(.0);
	outCol = vec4(col, 1.0);
}