//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
#define ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H

#include "asengine.h"
#include <string>

//include game objects
#include "Sumo/Sumo.h"
#include "Terrain/Terrain.h"
#include "CameraController/CameraController.h"
#include "Ball/Ball.h"
#include "Ball/BallSolo/BallSolo.h"
#include "Ball/BallVs/BallVs.h"
#include "UI/Button/Button.h"
#include "UI/TitleScreen/TitleScreen.h"
#include "UI/Button/ButtonParticle.h"
#include "UI/TransitionManager/TransitionManager.h"
#include "UI/SplashScreen/SplashScreen.h"
#include "System/ScoreManager/ScoreManager.h"
#include "UI/HudVs/HudVs.h"
#include "System/SoloManager/SoloManager.h"
#include "UI/HudSolo/HudSolo.h"
#include "UI/Pause/PauseMenu.h"

#include "Sumo/online/SumoC.h"
#include "Sumo/online/SumoR.h"
#include "Ball/BallVs/BallVSon.h"


#include "System/SettingManager/SettingManager.h"
#include "UI/SettingScreen/SettingScreen.h"
#include "UI/ButtonToggle/ButtonToggle.h"
#include "UI/ScrollingBackground/ScrollingBackground.h"
#include "UI/OnlineScreen/OnlineScreen.h"
#include "UI/ButtonToggle/KeypadButton.h"


//add every game object here
static void loadGameObjects() {
	ASEngine::Instance::addGameObject<Sumo>("SumoRed");
	ASEngine::Instance::addGameObject<Sumo>("SumoBlue");
	ASEngine::Instance::addGameObject<SumoR>("SumoR");
	ASEngine::Instance::addGameObject<SumoC>("SumoC");
	ASEngine::Instance::addGameObject<Terrain>("Terrain");
	ASEngine::Instance::addGameObject<CameraController>("CameraController");
	ASEngine::Instance::addGameObject<PauseMenu>("pause");
	ASEngine::Instance::addGameObject<BallVs>("BallVs");
	ASEngine::Instance::addGameObject<BallVson>("BallVson");
	ASEngine::Instance::addGameObject<BallSolo>("BallSolo");
	ASEngine::Instance::addGameObject<Button>("Button");
	ASEngine::Instance::addGameObject<ButtonParticle>("ButtonParticle");
	ASEngine::Instance::addGameObject<TitleScreen>("TitleScreen");
	ASEngine::Instance::addGameObject<TransitionManager>("TransitionManager");
	ASEngine::Instance::addGameObject<SplashScreen>("SplashScreen");
	ASEngine::Instance::addGameObject<ScoreManager>("ScoreManager");
	ASEngine::Instance::addGameObject<HudVs>("HudVs");
	ASEngine::Instance::addGameObject<HudSolo>("HudSolo");
	ASEngine::Instance::addGameObject<SoloManager>("SoloManager");
	ASEngine::Instance::addGameObject<SettingManager>("SettingManager");
	ASEngine::Instance::addGameObject<SettingScreen>("SettingScreen");
	ASEngine::Instance::addGameObject<ButtonToggle>("ButtonToggle");
	ASEngine::Instance::addGameObject<KeypadButton>("Keypad");
	ASEngine::Instance::addGameObject<ScrollingBackground>("ScrollingBackground");
	ASEngine::Instance::addGameObject<OnlineScreen>("OnlineScreen");
}

#endif //ANDROIDSIMPLEENGINE_LOADGAMEOBJECT_H
