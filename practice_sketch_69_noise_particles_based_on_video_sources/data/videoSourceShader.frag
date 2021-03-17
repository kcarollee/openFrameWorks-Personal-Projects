#version 150

uniform vec2 resolution;
uniform sampler2D videoTex;
uniform float windowDiv;
out vec4 outCol;

void main(){
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	//uv.y = 1.0 - uv.y;
	vec2 uvo = uv; // copy of the original uv coordinates
	float m = 0.1; // pixelate coef
	uv.x = float (floor(uv.x / windowDiv)) * windowDiv;
	uv.y = float(floor(uv.y / windowDiv)) * windowDiv;
	//if (uv.x > uv.y) uv = uvo;
	vec3 texCol = texture2D(videoTex, uv).rgb;
	texCol = vec3((texCol.r + texCol.g + texCol.b) / 3.0); // greyscale
	outCol = vec4(texCol, 1.0);
}