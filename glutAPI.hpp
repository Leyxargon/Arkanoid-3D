#ifndef _GLUT_OO
#define _GLUT_OO

#include "wrapper.hpp"

namespace glutAPI {

	class GlutAPI {
	private:
		static GlutAPI* instance;

		virtual void display() = 0;
		virtual void reshape(int, int) {};
		virtual void mousePress(int, int, int, int) {};
		virtual void mouseMotion(int, int) {};
		virtual void mousePassiveMotion(int, int) {};
		virtual void keyboard(unsigned char, int, int) {};
		virtual void keyboardDown(unsigned char, int, int) {};
		virtual void keyboardUp(unsigned char, int, int) {};
		virtual void specialKeyboardDown(int, int, int) {};
		virtual void specialKeyboardUp(int, int, int) {};
		
	protected:
		void setInstance();
		void clearInstance();

		static void displayWrapper();
		static void reshapeWrapper(int, int);
		static void mousePressWrapper(int, int, int, int);
		static void mouseMotionWrapper(int, int);
		static void mousePassiveMotionWrapper(int, int);
		static void keyboardWrapper(unsigned char, int, int);
		static void keyboardDownWrapper(unsigned char, int, int);
		static void keyboardUpWrapper(unsigned char, int, int);
		static void specialKeyboardDownWrapper(int, int, int);
		static void specialKeyboardUpWrapper(int, int, int);
	};
}

#endif
