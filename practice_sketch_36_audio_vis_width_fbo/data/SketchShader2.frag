#version 430

in vec2 fragUV;
out vec4 outColor;
uniform float time;
uniform float soundVal;
uniform float randf;
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
void main(){
	vec3 col = vec3(0);
	vec2 uv = fragUV;
	vec2 center = vec2(0.5);
	float circle = tan(time * soundVal + length(uv - vec2(rand(vec2(uv.x)), rand(vec2(uv.y))) * 0.05 * sin(time) -  center) * 20);
	col += circle;
	outColor = vec4(col, 1.0);
	outColor.r = 0.7 + 0.2 * sin(time + randf);
	outColor.g = 0.4 + 0.4 * cos(time * 3 + rand(uv + time));
	outColor.b += rand(uv + randf);
}