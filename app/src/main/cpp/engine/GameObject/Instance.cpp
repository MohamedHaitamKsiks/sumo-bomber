//
// Created by ksiks_wa3r on 3/24/23.
//

#include "Instance.h"

namespace ASEngine {

	std::vector<GameObject*> Instance::instances = {};

	std::vector<GameObject*> Instance::destroyQueue = {};

	float Instance::timeScale = 1.0f;

	GameObject *Instance::create(GameObjectID name) {
		GameObject* instance = gameObjects[name]();
		instance->objectId = name;
		instance->onCreate();
		return instance;
	}

	void Instance::destroy(GameObject *instance) {
		//find instance index
		destroyQueue.push_back(instance);
		instance->enable = false;

	}

	void Instance::destroyAll() {
		for (auto instance: instances) {
			destroy(instance);
		}
	}

	void Instance::update(float delta) {
		for (auto instance: instances) {
			//check if enable
			if (!instance->enable)
				continue;
			//update
			instance->mask.position = instance->position;
			instance->onUpdate(delta * timeScale);
		}
		cleanDestroyQueue();
	}

	void Instance::draw(Graphics& graphics) {
		for (auto instance: instances) {
			//check if enable
			if (!instance->enable || !instance->visible)
				continue;
			instance->onDraw(graphics);
		}
	}


	void Instance::cleanDestroyQueue() {
		//free all
		for (auto instance: destroyQueue) {
			std::remove(instances.begin(), instances.end(), instance);
			instances.pop_back();
			//delete instance;
		}
		destroyQueue.clear();
		//ALOG("instances : %d", instances.size());

	}

	//link game object name to object
	std::unordered_map<std::string, GameObject* (*) ()> Instance::gameObjects = {};

	//find
	GameObject *Instance::find(const GameObjectID &name) {
		for (auto instance: Instance::instances) {
			if (instance->objectId == name) {
				return instance;
			}
		}
		return nullptr;
	}


} // ASEngine