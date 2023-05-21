//
// Created by ksiks_wa3r on 4/18/23.
//

#include "CameraController.h"


void CameraController::onCreate() {
	persistant = true;
}

void CameraController::onUpdate(float delta) {
	if (time < dur) {
		Camera::current->offset = vec2::one().rotate(rotation) * mag * sin(time * 2.0f * M_PI * freq) * (1.0f - time / dur);
		time += delta;
	}

	//slow motion timer
	slowMotionTimer -= delta;

	if (slowMotionEnabled && slowMotionTimer < 0.0f) {
		Instance::timeScale = 1.0f;
		slowMotionEnabled = false;
	}
}

//start camera shake
void CameraController::shake(float _mag, float _dur, float _freq) {
	mag = _mag;
	dur = _dur;
	freq = _freq;
	rotation = Random::rand_rangef(0.0f, 2.0f * M_PI);
	time = 0.0f;
}


void CameraController::onDraw(Graphics &graphics) {

}

void CameraController::onInputEvent(InputEvent event) {

}

void CameraController::slowMotion(float _scale, float _dur) {
	Instance::timeScale = _scale;
	slowMotionTimer = _dur * _scale;
	slowMotionEnabled = true;
}

