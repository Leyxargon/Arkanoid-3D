#include "menu.hpp"

Menu::Menu() {
	setInstance();
	scena = MAIN;
	cam3D = false;
	scene.push_back(0);
}

Menu::Menu(unsigned int p) : Menu() {
	scena = GAMEOVER;
	input = "";
	punteggio = p;
}

void Menu::render() {
	glutCreateWindow("Arkanoid 3D");
	glutDisplayFunc(displayWrapper);
	glutReshapeFunc(reshapeWrapper);
	glutMouseFunc(mousePressWrapper);
	glutMotionFunc(mouseMotionWrapper);
	glutPassiveMotionFunc(mousePassiveMotionWrapper);
	glutKeyboardFunc(keyboardWrapper);

	// carica texture menu
	scene = { loadTexture("menu/main_0.bmp") };
	scene.push_back(loadTexture("menu/main_1.bmp"));
	scene.push_back(loadTexture("menu/main_2.bmp"));
	scene.push_back(loadTexture("menu/main_3.bmp"));
	scene.push_back(loadTexture("menu/main_4.bmp"));
	scene.push_back(loadTexture("menu/highscores_0.bmp"));
	scene.push_back(loadTexture("menu/highscores_1.bmp"));
	scene.push_back(loadTexture("menu/settings_0.bmp"));
	scene.push_back(loadTexture("menu/settings_1.bmp"));
	scene.push_back(loadTexture("menu/settings_2.bmp"));
	scene.push_back(loadTexture("menu/settings_3.bmp"));
	scene.push_back(loadTexture("menu/settings_4.bmp"));
	scene.push_back(loadTexture("menu/settings_5.bmp"));
	scene.push_back(loadTexture("menu/gameover_highscore_0.bmp"));

	if (scena == MAIN)
		img = &scene.at(0);
	else if (scena == GAMEOVER)
		img = &scene.at(13);

	glutMainLoop();
}

void Menu::display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *img);

	// Render Settings
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glColor3ub(0,0,0);

	glBegin(GL_QUADS);
		// Top Left
		glTexCoord2f(0, 1);
		glVertex2f(0, 0 + 600);

		// Top Right
		glTexCoord2f(1, 1);
		glVertex2f(0 + 800, 0 + 600);

		// Bottom Right
		glTexCoord2f(1, 0);
		glVertex2f(0 + 800, 0);

		// Bottom Left
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
	glEnd();

	if (scena == SCORES)
		visualizzaPunteggi();
	else if (scena == GAMEOVER)
		immettiNomeGiocatore();

	glutSwapBuffers();
}

void Menu::reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutReshapeWindow(800, 600);
	glutPostRedisplay();
}

void Menu::mousePress(int button, int state, int x, int y) {
	switch (button | state) {
	case GLUT_LEFT_BUTTON | GLUT_UP:
		if (scena == MAIN) {
			if (tastoPremuto(x, y, 250, 292, 548, 326)) { // NEW GAME
				clearInstance();
				glutDestroyWindow(glutGetWindow());
				Arkanoid sessione(cam3D);
				sessione.render();
			}
			else if (tastoPremuto(x, y, 192, 372, 606, 406)) // HIGH SCORES
				scena = SCORES;
			else if (tastoPremuto(x, y, 255, 452, 542, 486)) { // SETTINGS
				scena = SETTINGS;
				if (!cam3D)
					img = &scene.at(7);
				else
					img = &scene.at(10);
			}
			else if (tastoPremuto(x, y, 332, 532, 468, 566)) // EXIT
				exit(0);
		}
		else if (scena == SCORES) {
			if (tastoPremuto(x, y, 322, 532, 472, 566))
				scena = MAIN;
		}
		else if (scena == SETTINGS) {
			if (cam3D) {
				if (tastoPremuto(x, y, 134, 372, 660, 406)) // PERSPECTIVE 3D
					cam3D = !cam3D;
				else if (tastoPremuto(x, y, 321, 451, 472, 485)) // BACK
					scena = MAIN;
			}
			else {
				if (tastoPremuto(x, y, 109, 372, 684, 406)) // PERSPECTIVE 2.5D
					cam3D = !cam3D;
				else if (tastoPremuto(x, y, 321, 451, 472, 485)) // BACK
					scena = MAIN;
			}
		}
		break;
	}
}

void Menu::mouseMotion(int x, int y) {}

void Menu::mousePassiveMotion(int x, int y) {
	if (scena == MAIN) {
		if (tastoPremuto(x, y, 250, 292, 548, 326)) // NEW GAME
			img = &scene.at(1);
		else if (tastoPremuto(x, y, 192, 372, 606, 406)) // HIGH SCORES
			img = &scene.at(2);
		else if (tastoPremuto(x, y, 255, 452, 542, 486)) // SETTINGS
			img = &scene.at(3);
		else if (tastoPremuto(x, y, 332, 532, 468, 566)) // EXIT
			img = &scene.at(4);
		else
			img = &scene.at(0);
	}
	else if (scena == SCORES) {
		if (tastoPremuto(x, y, 322, 532, 472, 566))
			img = &scene.at(6);
		else
			img = &scene.at(5);
	}
	else if (scena == SETTINGS) {
		if (cam3D) {
			if (tastoPremuto(x, y, 134, 372, 660, 406)) // PERSPECTIVE 3D
				img = &scene.at(11);
			else if (tastoPremuto(x, y, 321, 451, 472, 485)) // BACK
				img = &scene.at(12);
			else
				img = &scene.at(10);
		}
		else {
			if (tastoPremuto(x, y, 109, 372, 684, 406)) // PERSPECTIVE 2.5D
				img = &scene.at(8);
			else if (tastoPremuto(x, y, 321, 451, 472, 485)) // BACK
				img = &scene.at(9);
			else
				img = &scene.at(7);
		}
	}
	display();
}

void Menu::keyboard(unsigned char key, int x, int y) {
	if (scena == GAMEOVER) {
		if (key > 32 && key < 127 && input.size() < 20)
			input.push_back(key);
		else if (key == 8 && input.size() > 0)
			input.pop_back();
		else if (key == 13 && input.size() > 0) {
			punteggi.nuovoGiocatore({ input, punteggio });
			img = &scene.at(5);
			scena = SCORES;
		}
		display();
	}
	else {
		switch (key) {
		case 27:
			if (scena == MAIN)
				exit(0);
			else {
				img = &scene.at(0);
				scena = MAIN;
				display();
			}
			break;
		}
	}
}

void Menu::visualizzaPunteggi() {
	glDisable(GL_TEXTURE_2D);
	glColor3ub(255, 236, 84);
	int y = 0;
	for (auto t = punteggi.begin(); t != punteggi.end(); ++t) {
		glRasterPos3f(150, 450 - y, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)t->first.c_str());
		glRasterPos3f(580, 450 - y, 0.0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)to_string(t->second).c_str());
		y += 30;
	}
}

void Menu::immettiNomeGiocatore() {
	glDisable(GL_TEXTURE_2D);
	glColor3ub(255, 236, 84);
	glRasterPos3f(70.0, 385.0, 0.0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) input.c_str());
}

bool Menu::tastoPremuto(int x, int y, int x1_bottone, int y1_bottone, int x2_bottone, int y2_bottone) {
	return ( (x >= x1_bottone && x <= x2_bottone) && (y >= y1_bottone && y <= y2_bottone) );
}
