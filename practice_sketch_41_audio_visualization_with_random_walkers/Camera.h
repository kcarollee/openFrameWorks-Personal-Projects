#pragma once
#pragma once
#include "ofMain.h"
#include "ofEvents.h"
// keep in mind that the world lies on the xz coordinate 
// where the positive z coordinate is initially towards the viewer.

using namespace glm;

class Camera {
public:

	void setup(vec3 position, float fov, float movementSpeed) {
		this->position = position; this->fov = fov; this->movementSpeed = movementSpeed;
		cameraRotateUp = cameraRotateDown =
			cameraMoveForward = cameraMoveBackward =
			cameraMoveForward = cameraMoveBackward =
			cameraMoveLeft = cameraMoveRight = false;
		cameraMoved = true;
		rotateHori = rotateVert = 0.0f;
		viewDir = vec3(glm::cos(PI * 1.5), 0.0, glm::sin(PI  * 1.5));

		ofAddListener(ofEvents().keyPressed, this, &Camera::keyboardPressedHandler);
		ofAddListener(ofEvents().keyReleased, this, &Camera::keyboardReleasedHandler);
	}

	void cameraUpdate(mat4& view) {
		viewDir = normalize(viewDir);
		if (cameraMoveForward) position += movementSpeed * viewDir;
		else if (cameraMoveBackward) position -= movementSpeed * viewDir;

		// add the vector that is horizontal to the viewing direction, which is found by
		// taking the cross product of the normal vector of the xz plane and viewDir
		if (cameraMoveLeft) position += movementSpeed * normalize(cross(vec3(0, 1, 0), viewDir));
		else if (cameraMoveRight) position -= movementSpeed * normalize(cross(vec3(0, 1, 0), viewDir));

		if (cameraRotateDown) rotateVert -= movementSpeed;
		else if (cameraRotateUp) rotateVert += movementSpeed;

		// update the camera's view direction 
		if (cameraRotateLeft) {
			rotateHori += movementSpeed;
			viewDir.x = glm::cos(PI * 1.5 - rotateHori);
			viewDir.z = glm::sin(PI * 1.5 + rotateHori);
		}
		else if (cameraRotateRight) {
			rotateHori -= movementSpeed;
			viewDir.x = glm::cos(PI * 1.5 - rotateHori);
			viewDir.z = glm::sin(PI * 1.5 + rotateHori);
		}
		view = inverse(translate(position)*
			rotate(rotateHori, vec3(0, 1, 0))*
			rotate(rotateVert, vec3(1, 0, 0)));
	}

	void keyboardPressedHandler(ofKeyEventArgs & keyEvent) {
		cameraMoved = true;
		switch (keyEvent.key) {
		case 'w':
			cameraMoveForward = true;

			break;

		case 's':
			cameraMoveBackward = true;
			break;
		case 'a':
			cameraMoveLeft = true;
			break;
		case 'd':
			cameraMoveRight = true;
			break;
		case OF_KEY_UP:
			cameraRotateUp = true;
			break;
		case OF_KEY_DOWN:
			cameraRotateDown = true;
			break;
		case OF_KEY_LEFT:
			cameraRotateLeft = true;

			break;
		case OF_KEY_RIGHT:
			cameraRotateRight = true;
			break;
		}
	}

	void keyboardReleasedHandler(ofKeyEventArgs& keyEvent) {
		//cameraMoved = false;
		switch (keyEvent.key) {
		case 'w':
			cameraMoveForward = false;
			break;

		case 's':
			cameraMoveBackward = false;
			break;
		case 'a':
			cameraMoveLeft = false;
			break;
		case 'd':
			cameraMoveRight = false;
			break;
		case OF_KEY_UP:
			cameraRotateUp = false;
			break;
		case OF_KEY_DOWN:
			cameraRotateDown = false;
			break;
		case OF_KEY_LEFT:
			cameraRotateLeft = false;
			break;
		case OF_KEY_RIGHT:
			cameraRotateRight = false;
			break;


		}
	}


public:
	vec3 position;
	vec3 viewDir;
	float fov;
	float rotateHori, rotateVert;
	float movementSpeed;
	bool cameraRotateLeft, cameraRotateRight,
		cameraRotateUp, cameraRotateDown,
		cameraMoveForward, cameraMoveBackward,
		cameraMoveLeft, cameraMoveRight;
	bool cameraMoved;
	//bool keyIsDown[255];
};