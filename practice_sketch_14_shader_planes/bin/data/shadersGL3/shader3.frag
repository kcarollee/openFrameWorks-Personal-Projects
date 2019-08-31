#version 150

out vec4 outputColor;
uniform float time;
uniform float random;
void main()
{
    float windowWidth = 700;
    float windowHeight = 700;
	float timePassed = time;
	
	float r =  gl_FragCoord.y / windowHeight * tan(gl_FragCoord.y + time) * 10;
	float g = gl_FragCoord.y / windowHeight * cos(gl_FragCoord.y * time) * 10;
	float b = gl_FragCoord.x / windowHeight * sin(gl_FragCoord.x * time) * 4;;
	float a = 50.0;
	float avg = (r + g + b) / 3;
	outputColor = vec4(avg, avg / 2, avg / 4, a);
}