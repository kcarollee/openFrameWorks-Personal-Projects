#version 430
uniform float time;
uniform vec3 lightDir;
uniform vec3 lightCol;
uniform sampler2D normTex;
uniform vec3 cameraPos;
uniform vec3 meshCol;
uniform int discardMode;
uniform float discardThreshold;
uniform float exponent;
in vec2 fragUV;
in vec2 fragUV2;
in vec3 fragNrm;
in vec3 fragWorldPos;
in mat3 TBN;

out vec4 outColor;


void main(){
	vec3 nrm = texture(normTex, fragUV).rgb;
	nrm = (nrm * 2.0 - 1.0);   
	
	
	vec3 nrm2 = texture(normTex, fragUV2).rgb;
	nrm2 = (nrm2 * 2.0 - 1.0);   
	
	nrm = normalize(TBN *(nrm + nrm2)); 
	
	

	vec3 viewDir = normalize(vec3(0) - fragWorldPos); 	
	vec3 halfVec = normalize((vec3(0) - lightDir));
	
	float diffAmt = max(0.0, dot(nrm, -lightDir));
	vec3 diffCol = meshCol * lightCol * diffAmt;

	float specAmt = max(0.0, dot(halfVec, nrm));
	float specBright = pow(specAmt, exponent);
	
	vec3 specCol = lightCol * specBright;

	
	outColor = vec4(diffCol + specCol , 0.7); 
	if (discardMode == 1) {
		if (
			(outColor.r + outColor.g + outColor.b) /3.0 < discardThreshold) discard;
	}
	
}