#version 430
uniform int seedNum; // half of seedArr's size
uniform int sourceNum; // number of textures
uniform int textureIndex;
uniform bool discardMode, greyScaleMode;
uniform vec2 seeds[15]; // half of seedArr's size
uniform float time;
uniform float greyScaleVal[15];// half of seedArr's size
uniform sampler2D tex;

in vec2 fragUV;
out vec4 outColor;

// for debugging
float circle(vec2 st, vec2 pos, float r){
	return step(length(st - pos), r);
}


void main(){
	vec2 uv = fragUV;
	vec4 textureImg = texture(tex, uv);
	float dist = distance(seeds[0], uv);
    vec3 color = vec3(greyScaleVal[0]);

	vec3 compColor = vec3(0.0);

	// voronoi 
    for (int i = 1; i < seedNum; i++) {
        float current = distance(seeds[i], uv);
        if (current < dist) {
            color = vec3(greyScaleVal[i]);
            dist = current;
        }
    }
	compColor += dist;


	// greyscale
	if (greyScaleMode) {
		if (discardMode) if (color.r < 0.5) discard;
		else outColor = vec4(color, 1.0);
	}
	// texture
	else {
		float grey;
		if (abs(color.x - (1.0 / float(seedNum)) * float(textureIndex)) < 0.01) {
			grey = color.x;
			color = textureImg.rgb;
			//color *= 1.0 - 3.0 * compColor;
			//if (1.0 - 3.0 * compColor.x < 0.2) discard;
		}
		else discard;
		if (discardMode) if (grey > 0.5) discard;
		else outColor = vec4(color, 1.0);
	}
	outColor = vec4(color, 1.0);
}
