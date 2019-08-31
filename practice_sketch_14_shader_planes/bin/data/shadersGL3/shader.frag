#version 150

out vec4 outputColor;
uniform float time;
uniform float random;
void main()
{

    float windowWidth = 700;
    float windowHeight = 700;
	float timePassed = time;
	
	float r = gl_FragCoord.x / windowWidth * sin(gl_FragCoord.x * time + time) * 4;
	float g = gl_FragCoord.y / windowHeight * cos(gl_FragCoord.y * time + time) * 4;
	float b = gl_FragCoord.x / windowHeight * cos(gl_FragCoord.x * time + time) * 4;;
	float a = 1.0;
	float avg = (r + g + b) / 3;
	outputColor = vec4(avg / 4, avg / 2, avg, a);
}