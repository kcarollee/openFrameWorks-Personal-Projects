#version 150
uniform vec2 resolution;
uniform vec2 mouse;
uniform float random;
uniform float radius;
uniform float time;

out vec4 outputColor;

float plot(vec2 norm, float target)
{
	return smoothstep(target -(0.0051 + 0.005 * sin(time * 1.5)), target, norm.y) - 
	smoothstep(target, target + 0.0051 + 0.005 * sin(time * 1.5), norm.y);
}
void main(void)
{

  vec2 norm = gl_FragCoord.xy / resolution;
  const int lineNum = 100;
  float funcs[lineNum];
  float pts[lineNum];
  // functions to plot
  // keep in mind that every coordinate is normalized
  for (int i = 0; i < funcs.length(); i++){
	funcs[i] = 0.5 + tan(time / 12 + i / 2) * 
	(0.5 + 0.3 * tan(time / 12)) *  
	tan(norm.x / (0.1 + 0.05 * sin(time/12)) - 0.5);
  }

  // points
  for (int i = 0; i < funcs.length(); i++){
	pts[i] = plot(norm, funcs[i]);
  }

  float sum = 0;
  for (int i = 0; i < funcs.length(); i++){
	sum += pts[i];
  }

  vec3 color = (sum) * vec3(0.5 + 0.2* sin(time),0.5 + 0.3 * cos(time), 0.8);

  outputColor =vec4(color, 1.0);

}