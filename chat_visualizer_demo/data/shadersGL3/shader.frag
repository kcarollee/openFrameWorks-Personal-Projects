#version 150

uniform float rectXpos;
uniform float rectYpos;
uniform float rectWidth;
uniform float rectHeight;
uniform float time;
uniform float random;
out vec4 outputColor;

float random2d(vec2 coord){
	if (10 < random && random <20){
		return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5454);
	}
	else if (20 < random && random < 30){
		return fract(cos(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5454);
	}
	else if (30 < random && random < 40){
		return fract(tan(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5454);
	}
	else if (40 < random && random < 50){
		return fract(sin(dot(coord.xy, vec2(15.23, 90.233))) * 43758.5454);
	}
	else if (50 < random && random < 60){
		return fract(tan(dot(coord.xy, vec2(54, 78.233))) * 43758.5454);
	}
	else if (60 < random && random < 70){
		return fract(cos(dot(coord.xy, vec2(2.9898, 8.233))) * 43758.5454);
	}
	else if (70 < random && random < 80){
		return fract(sin(dot(coord.xy, vec2(42.9898, 12.233))) * 43758.5454);
	}
	else if (80 < random && random < 90){
		return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 52358.5454);
	}
}

void main()
{ 
	vec2 position = vec2(rectXpos, rectYpos);
	vec2 dimensions = vec2(rectWidth, rectHeight);
	vec2 coordWithin = (gl_FragCoord.xy - dimensions) / 50;
	
	vec3 color = vec3(0.0);
	float grain = 0.0;
	grain = random2d(vec2(cos(coordWithin) / 9999999.9) * time);
	float r = (gl_FragCoord.x - rectXpos) * random / rectWidth;
	float g = (gl_FragCoord.y - rectYpos)  * random/ rectHeight;
	float b = 0;
	float a = 1.0;
	float avg = (r + g + b) / 3;
	color = vec3(grain) * random;
	
	if (10 < random && random <20){
		outputColor = vec4(grain * 30 / random, grain / random * 2, grain * 2 / random, 1.0);
	}
	else if (20 < random && random < 30){
		outputColor = vec4(grain  / random, grain * 40 / random * 2, grain * 2 / random, 1.0);
	}
	else if (30 < random && random < 40){
		outputColor = vec4(grain * 30 / random, grain / random * 2, grain * 2 / random, 1.0);
	}
	else if (40 < random && random < 50){
		outputColor = vec4(grain * 30 / random, grain / random * 2, grain * 50 / random, 1.0);
	}
	else if (50 < random && random < 60){
		outputColor = vec4(grain * 30 / random, grain * 30 / random * 2, grain * 2 / random, 1.0);
	}
	else if (60 < random && random < 70){
		outputColor = vec4(grain * 90 / random, grain / random * 2, grain * 2 / random, 1.0);
	}
	else if (70 < random && random < 80){
		outputColor = vec4(grain  / random, grain / random * 2, grain * 24/ random, 1.0);
	}
	else if (80 < random && random < 90){
		outputColor = vec4(grain * 12/ random, grain / random * 2, grain * 21/ random, 1.0);
	}
}