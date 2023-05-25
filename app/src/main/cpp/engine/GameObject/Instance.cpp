//
// Created by ksiks_wa3r on 3/24/23.
//

#include "Instance.h"

namespace ASEngine {

	std::vector<GameObject *> Instance::instances = {};

	std::map<uint32_t, std::vector<GameObject *>> Instance::layers = {};

	std::vector<GameObject *> Instance::destroyQueue = {};

	float Instance::timeScale = 1.0f;

	bool Instance::paused = false;

	bool Instance::showkeyboard = true;

	int Instance::textInputState = 1;

	int Instance::socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

	char* Instance::text = (char *) "";

	std::string Instance::ipaddr = "";
	std::string Instance::destipaddr = "";

	Instance::GameState Instance::gameState = Instance::GAME_PLAYING;

	GameObject *Instance::create(GameObjectID name) {
		GameObject *instance = gameObjects[name]();
		instance->objectId = name;
		instance->onCreate();
		return instance;
	}

	void Instance::destroy(GameObject *instance) {
		if (!instance->enable)
			return;
		//find instance index
		//destroyQueue.push_back(instance);
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
			if (instance->pausable) {
				if (!instance->enable || paused) {
					instance->mask.position = instance->position;
					layers[instance->layer].push_back(instance);
					continue;
				}
			}
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

	void Instance::draw(Graphics &graphics) {
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
	std::unordered_map<std::string, GameObject *(*)()> Instance::gameObjects = {};

	//find
	GameObject *Instance::find(const GameObjectID &name) {
		for (auto instance: Instance::instances) {
			if (instance->enable && instance->objectId == name) {
				return instance;
			}
		}
		return nullptr;
	}


	std::string Instance::server() {

		int enable = 1;
		setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
		sockaddr_in localAddress{};
		localAddress.sin_family = AF_INET;
		localAddress.sin_port = htons(8976);  // Example port number
		localAddress.sin_addr.s_addr = INADDR_ANY;  // Bind to any available interface
		int t = bind(socketDescriptor, reinterpret_cast<sockaddr *>(&localAddress), sizeof(localAddress));
		ALOG("bound with return state %i",t);
		if (t != 0) {
			// Handle bind error
			return "Error: Failed to bind the socket";
		}

		// Get the IP address of the bound socket
		char ipAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(localAddress.sin_addr), ipAddress, INET_ADDRSTRLEN);

		Instance::ipaddr = ipAddress;
		// Return the IP address as a string
		return ipAddress;

	}

	int Instance::Connect(char* addr="10.62.90.127" ) {
		sockaddr_in remoteAddress{};
		remoteAddress.sin_family = AF_INET;
		remoteAddress.sin_port = htons(8976);  // Example remote port number

		inet_pton(AF_INET, addr, &remoteAddress.sin_addr);  // Use  IP address

		int t = connect(socketDescriptor, reinterpret_cast<sockaddr *>(&remoteAddress),
						sizeof(remoteAddress));



		return t;
	}
}
// ASEngine