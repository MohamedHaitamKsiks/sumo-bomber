//
// Created by ksiks_wa3r on 3/27/23.
//

#include "InputEvent.h"

namespace ASEngine {
	void InputEvent::init(android_app *_app) {
		app = _app;
	}

	//pool event
	InputEvent InputEvent::poolEvent(const GameActivityMotionEvent* motionEvent, uint32_t ptrIndex) {
		//create event
		InputEvent event;

		int action = motionEvent->action;
		int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
		int actionPtrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		event.pointerIndex = motionEvent->pointers[actionPtrIndex].id;

		if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked == AMOTION_EVENT_ACTION_POINTER_DOWN) {
			event.type = INPUT_EVENT_POINTER_DOWN;
		} else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked == AMOTION_EVENT_ACTION_POINTER_UP) {
			event.type = INPUT_EVENT_POINTER_UP;
		} else if (actionMasked == AMOTION_EVENT_ACTION_MOVE) {
			event.type = INPUT_EVENT_POINTER_MOVE;
			event.pointerIndex = motionEvent->pointers[ptrIndex].id;
		}

		//get pointer position
		vec2 screenWindowRatio = vec2{
			float(Screen::getWindowWidth()) / float(Screen::getWidth()),
			float(Screen::getWindowHeight()) / float(Screen::getHeight())
		};

		event.pointerPosition.x = GameActivityPointerAxes_getX(&motionEvent->pointers[ptrIndex]) / screenWindowRatio.x;
		event.pointerPosition.y = GameActivityPointerAxes_getY(&motionEvent->pointers[ptrIndex]) / screenWindowRatio.y;

		//return event
		return event;
	}

	InputEvent InputEvent::poolKeyEvent(const GameActivityKeyEvent* keyEvent) {
		InputEvent event;

		event.pointerIndex = 0; // Set pointer index to 0 for key events

		if (keyEvent->action == AKEY_EVENT_ACTION_DOWN) {
			event.type = INPUT_EVENT_KEY_DOWN;
		} else if (keyEvent->action == AKEY_EVENT_ACTION_UP) {
			event.type = INPUT_EVENT_KEY_UP;
		}

		event.key = keyEvent->keyCode; // Store the key code

		return event;
	}

	//android app
	android_app* InputEvent::app = nullptr;




} // ASEngine