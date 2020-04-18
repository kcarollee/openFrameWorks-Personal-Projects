#version 430
uniform sampler2D videoTex;
uniform float radius, divw, divh;
uniform vec2 rectPos;
uniform int mode; // 0: hori, 1: vert, 2: rect, 3: circular
in vec2 fragUV;
out vec4 outColor;

vec3 horiRectArea(vec2 uv, vec2 pos, float h, vec3 col){
	if (uv.y < pos.y && uv.y > pos.y - h) return  col;
	else discard;
}
vec3 vertRectArea(vec2 uv, vec2 pos, float w, vec3 col){
	if (uv.x < pos.x && uv.x > pos.x - w) return  col;
	else discard;
}

vec3 rectArea(vec2 uv, vec2 pos, float w, float h, vec3 col){
	if (uv.x < pos.x + w / 2.0 && uv.x > pos.x - w / 2.0 &&
		uv.y < pos.y + h / 2.0 && uv.y > pos.y - h / 2.0) return  col;
	else discard;
}
vec3 circleArea(vec2 uv, float r, vec3 col){
	// center: 0.5, 0.5
	if (length(uv - vec2(0.5)) < r) return col;
	else discard;
}
void main(){
	vec3 outCol = texture(videoTex, fragUV).rgb;
	

	switch (mode){
	case 0:
		outColor = vec4(horiRectArea(fragUV, rectPos, divh, outCol), 1.0);
		break;
	case 1:
		outColor = vec4(vertRectArea(fragUV, rectPos, divw, outCol), 1.0);
		break;
	case 2:
		outColor = vec4(rectArea(fragUV, rectPos, divw, divh, outCol), 1.0);
		break;
	case 3:
		outColor = vec4(circleArea(fragUV, radius, outCol), 1.0);
		break;
	}
}