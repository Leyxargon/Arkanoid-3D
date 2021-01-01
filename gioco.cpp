#include "gioco.hpp"

Gioco::Gioco(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(LARGHEZZA_FINESTRA, ALTEZZA_FINESTRA);
	//glEnable(GL_DEPTH_TEST);
}

void Gioco::esegui() {
	menu.render();
}