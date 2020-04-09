#version 430
in vec2 fragCoord;
out vec4 outColor;
uniform float time;
uniform int intTime;
uniform int moveMode;
uniform bool isColored;
uniform sampler2D tex;

void main(){
	vec2 uv = fragCoord;
	vec4 tex = texture(tex, uv);
	outColor = tex;
	
	if (moveMode == 1){
		outColor.rgb += step(mod(uv.y * 30 + time, 2), 0.8 + 0.1 * sin(time));
		if (uv.y > 0.975 || uv.y < 0.025) {
			outColor.r = 0.0;
			outColor.b = 0.0;
			outColor.g = 0.0;
		}
	}

	else if (moveMode == 2){
		outColor.rgb += step(mod(uv.x * 30 + time, 2), 0.8 + 0.1 * sin(time));
		if (uv.x > 0.975 || uv.x < 0.025) {
			outColor.r = 0.0;
			outColor.b = 0.0;
			outColor.g = 0.0;
		}
	}
	else if (moveMode == 3 || moveMode == 0){
		outColor.rgb += step(mod(uv.x * 30 + time, 2), 0.5);
		if (uv.x > 0.975 || uv.x < 0.025) {
			outColor.r = 0.0;
			outColor.b = 0.0;
			outColor.g = 0.0;
		}
		outColor.rgb += step(mod(uv.y * 30 + time, 2), 0.8 + 0.1 * sin(time));
		if (uv.y > 0.975 || uv.y < 0.025) {
			outColor.r = 0.0;
			outColor.b = 0.0;
			outColor.g = 0.0;
		}
	}

	if (isColored){
		outColor.rgb = 1.0 - outColor.rgb;
	}

	outColor.rgb = 1.0 - outColor.rgb;
}