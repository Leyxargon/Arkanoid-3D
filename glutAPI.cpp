#include "glutAPI.hpp"

namespace glutAPI {
	GlutAPI* GlutAPI::instance = nullptr;

	void GlutAPI::setInstance() {
		if (instance == nullptr)
			instance = this;
	}

	void GlutAPI::clearInstance() {
		instance = nullptr;
	}

	void GlutAPI::displayWrapper() {
		instance->display();
	}

	void GlutAPI::reshapeWrapper(int w, int h) {
		instance->reshape(w, h);
	}

	void GlutAPI::mousePressWrapper(int button, int state, int x, int y) {
		instance->mousePress(button, state, x, y);
	}

	void GlutAPI::mouseMotionWrapper(int x, int y) {
		instance->mouseMotion(x, y);
	}

	void GlutAPI::mousePassiveMotionWrapper(int x, int y) {
		instance->mousePassiveMotion(x, y);
	}

	void GlutAPI::keyboardWrapper(unsigned char key, int x, int y) {
		instance->keyboard(key, x, y);
	}

	void GlutAPI::keyboardDownWrapper(unsigned char key, int x, int y) {
		instance->keyboardDown(key, x, y);
	}

	void GlutAPI::keyboardUpWrapper(unsigned char key, int x, int y) {
		instance->keyboardUp(key, x, y);
	}

	void GlutAPI::specialKeyboardDownWrapper(int key, int x, int y) {
		instance->specialKeyboardDown(key, x, y);
	}

	void GlutAPI::specialKeyboardUpWrapper(int key, int x, int y) {
		instance->specialKeyboardUp(key, x, y);
	}
}