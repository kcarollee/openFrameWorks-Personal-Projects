#include "ofApp.h"

// copy and pasted Practical Shader Development's calcTangent code
// https://github.com/Apress/practical-shader-dev/blob/master/ch11/2_DrawSkybox/ofApp.cpp
using namespace glm;
void calcTangents(ofMesh& mesh)
{
	
	vector<vec4> tangents;
	tangents.resize(mesh.getNumVertices());

	uint indexCount = mesh.getNumIndices();

	const vec3* vertices = mesh.getVerticesPointer();
	const vec2* uvs = mesh.getTexCoordsPointer();
	const uint* indices = mesh.getIndexPointer();

	for (uint i = 0; i < indexCount - 2; i += 3)
	{
		const vec3& v0 = vertices[indices[i]];
		const vec3& v1 = vertices[indices[i + 1]];
		const vec3& v2 = vertices[indices[i + 2]];
		const vec2& uv0 = uvs[indices[i]];
		const vec2& uv1 = uvs[indices[i + 1]];
		const vec2& uv2 = uvs[indices[i + 2]];

		vec3 edge1 = v1 - v0;
		vec3 edge2 = v2 - v0;
		vec2 dUV1 = uv1 - uv0;
		vec2 dUV2 = uv2 - uv0;

		float f = 1.0f / (dUV1.x * dUV2.y - dUV2.x * dUV1.y);

		vec4 tan;
		tan.x = f * (dUV2.y * edge1.x - dUV1.y * edge2.x);
		tan.y = f * (dUV2.y * edge1.y - dUV1.y * edge2.y);
		tan.z = f * (dUV2.y * edge1.z - dUV1.y * edge2.z);
		tan.w = 0;
		tan = normalize(tan);

		tangents[indices[i]] += (tan);
		tangents[indices[i + 1]] += (tan);
		tangents[indices[i + 2]] += (tan);
	}

	int numColors = mesh.getNumColors();

	for (int i = 0; i < tangents.size(); ++i)
	{
		vec3 t = normalize(tangents[i]);
		if (i >= numColors)
		{
			mesh.addColor(ofFloatColor(t.x, t.y, t.z, 0.0));
		}
		else
		{
			mesh.setColor(i, ofFloatColor(t.x, t.y, t.z, 0.0));
		}
	}
}
// xz coordinates
void buildFloorQuad(ofMesh& mesh, glm::vec3 pos, float width, float height) {
	ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };

	float uvcoords[8] = { 0,0, 1,0, 0,1, 1,1 };
	mesh.addVertex(pos);
	mesh.addVertex(glm::vec3(pos.x + width, pos.y, pos.z));
	mesh.addVertex(glm::vec3(pos.x, pos.y, pos.z + height));
	mesh.addVertex(glm::vec3(pos.x + width, pos.y, pos.z + height));

	mesh.addIndices(indices, 6);
	for (int i = 0; i < 4; i++) {
		mesh.addTexCoord(vec2(uvcoords[i * 2], uvcoords[i * 2 + 1]));
		mesh.addNormal(vec3(0, 1, 0));
	}
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofBackground(0);

	// camera
	using namespace glm;
	camera.setup(vec3(0, 0, 1), radians(90.0), 0.05);

	directionalLight.direction = normalize(vec3(0, -1, 1));
	directionalLight.color = vec3(1, 1, 1);
	directionalLight.intensity = 1.0f;

	// mvp matrix
	float aspect = (float)ofGetWidth() / (float)ofGetHeight();
	model = mat4();
	view = inverse(translate(camera.position));
	proj = perspective(camera.fov, aspect, 0.01f, 50.0f);
	mvp = proj * view * model;

	float width = 4.0;
	// zx coordinates (bottom)

	// yeah check out that code repeat 
	buildFloorQuad(bottom, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(bottom);
	buildFloorQuad(top, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(top);
	buildFloorQuad(left, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(left);
	buildFloorQuad(right, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(right);
	buildFloorQuad(front, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(front);
	buildFloorQuad(back, vec3(-width / 2.0, -width / 2.0, -width / 2.0), width, width);
	calcTangents(back);

	waterNormal.load("floorNormal.jpeg");
	waterNormal.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	waterShader.load("waterShader.vert", "waterShader.frag");


	gui.setup();
	gui.add(discardMode.set("enable discard", false));
	gui.add(discardThreshold.set("discard", 0.5, 0.0, 1.0));
	gui.add(exponent.set("exponent", 256.0, 0.0, 1024.0));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (camera.cameraMoved) {
		camera.cameraUpdate(view);
		mvp = proj * view * model;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	mat4 fmodel;
	mat3 normalMatrix;

	waterShader.begin();
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniformMatrix4f("model", model);
	waterShader.setUniform1f("time", ofGetElapsedTimef());
	waterShader.setUniformTexture("normTex", waterNormal, 0);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniform3f("lightCol", directionalLight.color);
	waterShader.setUniform3f("cameraPos", camera.position);
	waterShader.setUniform1i("discardMode", discardMode);
	waterShader.setUniform1f("discardThreshold", discardThreshold);
	waterShader.setUniform1f("exponent", exponent);
	fmodel = model;
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = vec3(0, -1, 0);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(0.2, 0.5, 0.8));
	bottom.draw();

	fmodel = rotate(radians(180.0f), vec3(0, 0, 1));
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = normalize(vec3(0, 1, 0));
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(0.6, 0.2, 0.5));
	top.draw();

	fmodel = rotate(radians(270.0f), vec3(0, 0, 1));
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = vec3(-1, 0, 0);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(0.4, 0.6, 0.7));
	left.draw();

	fmodel = rotate(radians(90.0f), vec3(0, 0, 1));
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = vec3(1, 0, 0);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(0.1, 0.7, 1.0));
	right.draw();

	fmodel = rotate(radians(90.0f), vec3(1, 0, 0));
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = vec3(0, 0, -1);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(0.2, 0.1, 0.7));
	back.draw();


	fmodel = rotate(radians(-90.0f), vec3(1, 0, 0));
	mvp = proj * view * fmodel;
	normalMatrix = mat3(transpose(inverse(fmodel)));
	directionalLight.direction = vec3(0, 0, 1);
	waterShader.setUniform3f("lightDir", directionalLight.direction);
	waterShader.setUniformMatrix3f("normal", normalMatrix);
	waterShader.setUniformMatrix4f("mvp", mvp);
	waterShader.setUniform3f("meshCol", vec3(1.0, 0.5, 0.2));
	front.draw();

	waterShader.end();

	ofDisableDepthTest();
	gui.draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
