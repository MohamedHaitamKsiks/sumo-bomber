//
// Created by ksiks_wa3r on 3/24/23.
//

#include "Instance.h"

namespace ASEngine {

	std::vector<GameObject*> Instance::instances = {};

	std::map<uint32_t, std::vector<GameObject*>> Instance::layers = {};

	std::vector<GameObject*> Instance::destroyQueue = {};

	float Instance::timeScale = 1.0f;

	bool Instance::paused = false;

	Instance::GameState Instance::gameState = Instance::GAME_PLAYING;

	GameObject *Instance::create(GameObjectID name) {
		GameObject* instance = gameObjects[name]();
		instance->objectId = name;
		instance->onCreate();
		return instance;
	}

	void Instance::destroy(GameObject *instance) {
		if (!instance->enable)
			return;
		//find instance index
		destroyQueue.push_back(instance);
		instance->enable = false;

	}

	void Instance::destroyAll() {
		for (auto instance: instances) {
			//don't destroy persistant objects
			if (instance->persistant)
				continue;
			destroy(instance);
		}
	}

	void Instance::update(float delta) {
		//clean layers
		layers.clear();
		//update instance
		for (auto instance: instances) {
			//check if enable
			if (instance->pausable){
			if (!instance->enable || paused){
                instance->mask.position = instance->position;
                layers[instance->layer].push_back(instance);
				continue;}}
			//update
            if (instance->enable) {
                instance->mask.position = instance->position;
                instance->onUpdate(delta * Instance::timeScale);
                layers[instance->layer].push_back(instance);
                //add to corresponding layer
            }
		}
		cleanDestroyQueue();
	}

	void Instance::draw(Graphics& graphics) {
		for (auto layer: layers) {
			for (auto instance: layers[layer.first]) {
				//check if enable
				if (!instance->enable || !instance->visible)
					continue;
				instance->onDraw(graphics);
			}
		}
	}


	void Instance::cleanDestroyQueue() {
		if (destroyQueue.size() == 0)
			return;
		//free all
		for (auto instance: destroyQueue) {
			std::remove(instances.begin(), instances.end(), instance);
			instances.pop_back();
			//delete instance;
		}
		destroyQueue.clear();

		//ALOG("instances : %d", instances.size());

	}
	void Instance::togglePause() {
		if (gameState == GAME_PLAYING) {
			gameState = GAME_PAUSED;
			paused = true;
			// Perform actions to pause the game (e.g., stop animations, pause physics, etc.)
			// Show the pause menu UI or perform other relevant tasks
		} else if (gameState == GAME_PAUSED) {
			gameState = GAME_PLAYING;
			paused = false;
			// Perform actions to resume the game (e.g., resume animations, resume physics, etc.)
			// Hide the pause menu UI or perform other relevant tasks
		}
	}


	//link game object name to object
	std::unordered_map<std::string, GameObject* (*) ()> Instance::gameObjects = {};

	//find
	GameObject *Instance::find(const GameObjectID &name) {
		for (auto instance: Instance::instances) {
			if (instance->enable && instance->objectId == name) {
				return instance;
			}
		}
		return nullptr;
	}


} // ASEngine