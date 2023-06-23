//
// Created by ksiks_wa3r on 5/23/23.
//

#include "SettingManager.h"
OboeSinePlayer sinePlayer;
void SettingManager::onCreate() {
	//make setting manager persistant in all scenes
	audio=true;
	persistant = true;
	//start audio
	//sinePlayer.startAudio();
	//isPlaying = true;
}

void SettingManager::onUpdate(float delta) {

	//stop audio
	if(!audio && isPlaying) {
		sinePlayer.stopAudio();
		isPlaying = false;
	}

	if (audio && !isPlaying) {
		sinePlayer.startAudio();
		isPlaying = true;
	}

}

void SettingManager::onDraw(Graphics &graphics) {

}

void SettingManager::onInputEvent(InputEvent event) {

}
