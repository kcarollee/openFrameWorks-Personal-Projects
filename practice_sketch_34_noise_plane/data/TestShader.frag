#version 430
#define MAX_ITERATIONS 10
in vec2 fragUV;
out vec4 outColor;
uniform float time;
uniform int greyScale;
uniform sampler2D noiseTex;
vec2 mandelbrot(vec2 c){
	vec2 z = vec2(0.0);
	uint i = 0;

	while ( i < MAX_ITERATIONS && (z.x * z.x + z.y * z.y) < 4.0){
		z = vec2(z.x * z.x - z.y * z.y + c.x, 2 * z.x * z.y + c.y);
		i++;
	}
	return z;
}
void main(){	
	
	outColor = texture(noiseTex, fragUV);
	
	
	
	
	if (greyScale == 1){
		float colorVal = mod(floor(outColor.r * 100), 5);
		outColor = vec4(vec3(colorVal), 1.0);
	}
	else if (greyScale == 2){

		outColor = vec4(vec3(mandelbrot(outColor.rb), 0.5 + 0.5 * sin(time * 4.0)), 1.0);
	}
	
}