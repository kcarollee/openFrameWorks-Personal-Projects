#version 150

uniform vec2 resolution;
uniform sampler2D sketchTex;
uniform sampler2D videoSource;
out vec4 outCol;

// the purpose of this shader is to combine the particle sketch with the source video in a way that
// it looks like the particles are drawn on top of the video.
// couldn't get it to work properly since the midbuffer gets darker instead of getting paler, which i guess it's supposed to be like that.
void main(){
	vec2 uv = gl_FragCoord.xy / resolution.xy;
	uv.y = 1.0 - uv.y;
	//uv.x = 1.0 - uv.x;
	vec3 st = texture(sketchTex, uv).rgb;
	vec3 vs = texture(videoSource, uv).rgb;
	if ((st.r + st.b + st.g) > 0.01) {
		outCol = vec4(st , 1.0);
		//if ((outCol.r + outCol.b + outCol.g) < 0.1) outCol.rgb += vs;
	}
	else outCol = vec4(vs, 1.0);
	//if ((outCol.r + outCol.b + outCol.g) / 3.0 < 0.001) outCol.rgb += vs;

	//outCol = vec4((st + vs), 1.0);
	outCol = vec4(st * 2.0, 1.0);
	//if ((outCol.r + outCol.g + outCol.b) / 3.0 == 0.0) discard;
	//outCol = vec4(vec3(st + vs), 1.0);
}