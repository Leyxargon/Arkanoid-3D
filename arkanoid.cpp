#include "arkanoid.hpp"

GLuint Arkanoid::sfondo = 0;
GLuint Arkanoid::bordo_v = 0;
GLuint Arkanoid::bordo_o = 0;

Arkanoid::Arkanoid() {
	setInstance();
	cam3D = false;

	x = 0;
	y = 0;
	z = 30;
	sfondo = bordo_v = bordo_o = 0;

	pausa = false;

	vite = 3;
	punteggio = cont_vite_punteggio = 0;
	i_livello = 0;

	for (int i = 0, x = 0; i < vite - 1; i++)
		viteHUD.push_back(Pedana(BORDOGIU - 10 + (x += 2), BORDOGIU - 5));

	livelli.push_back(new Livello1());
	livelli.push_back(new Livello2());
	livelli.push_back(new Livello3());
	livelli.push_back(new Livello4());
	livelli.push_back(new Livello5());
	livelli.push_back(new Livello6());
	livello = livelli.at(i_livello);
}

Arkanoid::Arkanoid(bool c) : Arkanoid() {
	if (cam3D = c) {
		x = -10;
		y = -20;
		z = 32;
	}
}

void Arkanoid::render() {
	glutCreateWindow("Arkanoid 3D");
	glutDisplayFunc(displayWrapper);
	glutReshapeFunc(reshapeWrapper);
	glutKeyboardFunc(keyboardWrapper);
	glutSpecialFunc(specialKeyboardDownWrapper);
	glutSpecialUpFunc(specialKeyboardUpWrapper);
	glutMainLoop();
}

void Arkanoid::cambiaCamera() {
	if (cam3D = !cam3D) { // 3D
		x = -10;
		y = -20;
		z = 32;
	}
	else { // 2.5D
		x = 0;
		y = 0;
		z = 30;
	}
}

void Arkanoid::renderHUD() {
	glDisable(GL_TEXTURE_2D);
	// scrittura punti
	glPushMatrix();
	// scrittura 1UP
	glColor3ub(255, 0, 0);
	glRasterPos2d(cam3D ? 29 : -20, cam3D ? 7 : 22);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) "1UP");

	// scrittura cifra vite
	glColor3ub(255, 255, 255);
	glRasterPos2d(cam3D ? 28.3 : -20, cam3D ? 5 : 21);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) to_string(punteggio).c_str());
	glPopMatrix();

	// scrittura punteggio massimo
	glPushMatrix();
	// scrittura HIGH SCORE
	glColor3ub(255, 0, 0);
	glRasterPos2f(cam3D ? 29 : -2, cam3D ? 17 : 22);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) (cam3D ? "HIGH\n SCORE" : "HIGH SCORE"));
	// scrittura punteggio
	glColor3ub(255, 255, 255);
	glRasterPos2d(cam3D ? 29 : -2, cam3D ? 12 : 21);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) (punteggio > topPunteggi.getPunteggioCampione() ? to_string(punteggio).c_str() : to_string(topPunteggi.getPunteggioCampione()).c_str()));
	glPopMatrix();

	// scrittura punteggio
	glPushMatrix();
	// scrittura STAGE
	glColor3ub(255, 0, 0);
	glRasterPos2d(cam3D ? 28 : 16, cam3D ? -16 : 22);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) "STAGE");
	// scrittura livello
	glColor3ub(255, 255, 255);

	glRasterPos2d(cam3D ? 32 : 16, cam3D ? -17 : 21);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) to_string(i_livello + 1).c_str());
	glPopMatrix();

	if (pausa) {
		glPushMatrix();
		glColor3ub(255, 255, 255);
		glRasterPos2f(-2, -10);
		glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) "PAUSE");
		glPopMatrix();
	}
	// vite
	for (auto ii = viteHUD.begin(); ii != viteHUD.end(); ++ii)
		ii->renderVita();
}

void Arkanoid::renderScene() {
	pedana.render();

	if (!pausa && vite > 0) {
		// aggiorna mattoni
		livello->render();

		// collisione pedana con i bordi
		if (pedana.getPosx() < BORDOSX + 1)
			pedana.setPosx(BORDOSX + 1);
		if (pedana.getPosx() > BORDODX - pedana.getDimx() - 1)
			pedana.setPosx(BORDODX - pedana.getDimx() - 1);

		// movimento pedana
		if (pedana.getMuovesx())
			pedana.setPosx(pedana.getPosx() - pedana.getVelx());
		if (pedana.getMuovedx())
			pedana.setPosx(pedana.getPosx() + pedana.getVelx());

		if (!palla.getFermo()) {
			glPushMatrix();
			palla.render();
			glPopMatrix();

			// movimento palla
			if (palla.muove(BORDOSX + 2, BORDODX, BORDOSU - 2).second < BORDOGIU - 3) {
				// vita persa
				--vite;
				palla.reset({ (pedana.getPosx() - 3) > BORDOSX ? pedana.getPosx() - 3 : pedana.getPosx() + 9, pedana.getPosy() + 10 }, { (pedana.getPosx() - 3) > BORDOSX ? 0.1 : -0.1, -0.1 });
				if (viteHUD.size() > 0)
					viteHUD.pop_back();
			}


			for (auto m = livello->begin(); m != livello->end();) {
				if (palla.collide(**m)) {
					(*m)->setSalute((*m)->getSalute() - 1);
					punteggio += (*m)->getValore();
					// bonus nuova vita
					if ((cont_vite_punteggio += (*m)->getValore()) >= 10000) {
						vite++;
						cont_vite_punteggio = 0;
						// aggiorna HUD
						if (!viteHUD.empty())
							viteHUD.push_back(Pedana(((--viteHUD.end())->getPosx() + 2), BORDOGIU - 5));
						else
							viteHUD.push_back(Pedana(BORDOGIU - 8, BORDOGIU - 5));
					}
					if ((*m)->getSalute() == 0)
						livello->rimuoviMattone(m);
				}
				else
					++m;
			}

			// collisione con la pedana
			palla.collide(pedana);
		}
		else // ferma la palla e reimposta posizione per il lancio
			palla.reset({ (pedana.getPosx() - 3) > -14 ? pedana.getPosx() - 3 : pedana.getPosx() + 9, pedana.getPosy() + 10 }, { (pedana.getPosx() - 3) > -14 ? 0.1 : -0.1, -0.1 });
	}
	else if (vite == 0) {
		// visualizza scritta GAME OVER
		glPushMatrix();

		glColor3ub(255, 255, 255);
		glRasterPos2f(-3, -10);
		glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char *) "GAME OVER");

		glPopMatrix();
	}

	// livello completato
	if (livello->getNumMattoni() == 0 && i_livello < livelli.size() - 1) {
		livello = livelli.at(++i_livello);
		palla.setFermo(true);
		palla.reset({ (pedana.getPosx() - 3) > -14 ? pedana.getPosx() - 3 : pedana.getPosx() + 9, pedana.getPosy() + 10 }, { (pedana.getPosx() - 3) > -14 ? 0.1 : -0.1, -0.1 });
	} // gioco completato
	else if (livello->getNumMattoni() == 0 && i_livello >= livelli.size() - 1) {
		palla.setFermo(true);

		glPushMatrix();

		glColor3ub(255, 255, 255);
		glRasterPos2f(-3.5, 0);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *) "VICTORY");

		glPopMatrix();
	}

	renderHUD();

	if (bordo_v == 0)
		bordo_v = loadTexture("texture/bordo_v.png");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bordo_v);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// bordo dx
	glPushMatrix();
	glColor3ub(147, 147, 147);
	glTranslated(BORDODX, -4.0, 0.0);
	glScaled(2, 42, 3);
	glutSolidCubeCustom(1);
	glPopMatrix();

	//bordo sx
	glPushMatrix();
	glColor3ub(147, 147, 147);
	glTranslated(BORDOSX, -4.0, 0.0);
	glScaled(2, 42, 3);
	glutSolidCubeCustom(1);
	glPopMatrix();

	if (bordo_o == 0)
		bordo_o = loadTexture("texture/bordo_o.png");

	// bordo superiore
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bordo_o);

	glPushMatrix();
	glColor3ub(147, 147, 147);
	glTranslated(0.0, BORDOSU, 0.0);
	glScaled(BORDODX * 2 + 2, 2, 3);
	glutSolidCubeCustom(1);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	if (sfondo == 0)
		sfondo = loadTexture("texture/sfondo.png");

	// sfondo del gioco
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sfondo);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTranslated(0.0, 0.0, -2.0);
	glBegin(GL_QUADS);

	// nord ovest
	glTexCoord2f(0, 1);
	glVertex2f(BORDOSX, BORDOSU);

	// nord est
	glTexCoord2f(1, 1);
	glVertex2f(BORDODX, BORDOSU);

	// sud est
	glTexCoord2f(1, 0);
	glVertex2f(BORDODX, BORDOGIU - 7);

	// sud ovest
	glTexCoord2f(0, 0);
	glVertex2f(BORDOSX, BORDOGIU - 7);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Arkanoid::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	GLfloat pos[] = { 10.0, 10.0, 50.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	renderScene();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Arkanoid::reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, (float) w / h, 1, 300);
	glMatrixMode(GL_MODELVIEW);
}

void Arkanoid::keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 13:
		if (vite == 0 || livello->getNumMattoni() == 0 && i_livello >= livelli.size() - 1) {
			clearInstance();
			glutDestroyWindow(glutGetWindow());
			if (punteggio > topPunteggi.getPunteggioUltimoGiocatore()) {
				Menu menu(punteggio);
				menu.render();
			}
			else {
				Menu menu;
				menu.render();
			}
		}
		break;
	case 27:
		if (vite > 0 && !pausa)
			pausa = !pausa;
		else if (vite > 0) {
			clearInstance();
			glutDestroyWindow(glutGetWindow());
			Menu menu;
			menu.render();
		}
		else if (vite == 0 || livello->getNumMattoni() == 0 && i_livello >= livelli.size() - 1) {
			clearInstance();
			glutDestroyWindow(glutGetWindow());
			if (punteggio > topPunteggi.getPunteggioUltimoGiocatore()) {
				Menu menu(punteggio);
				menu.render();
			}
			else {
				Menu menu;
				menu.render();
			}
		}
		break;
	case 'p':
	case 'P':
		if (vite > 0)
			pausa = !pausa;
		break;
	case 'c':
	case 'C':
		if (vite > 0 && !(livello->getNumMattoni() == 0 && i_livello >= livelli.size() - 1))
			cambiaCamera();
		break;
	case ' ':
		if (vite == 0 || livello->getNumMattoni() == 0 && i_livello >= livelli.size() - 1) {
			clearInstance();
			glutDestroyWindow(glutGetWindow());
			if (punteggio > topPunteggi.getPunteggioUltimoGiocatore()) {
				Menu menu(punteggio);
				menu.render();
			}
			else {
				Menu menu;
				menu.render();
			}
		}
		else if (palla.getFermo() && vite > 0 && !pausa)
			palla.setFermo(false);
		break;
	/*
	case '+':
		++i_livello;
		livello = livelli.at(i_livello);
		break;
	case '-':
		--i_livello;
		livello = livelli.at(i_livello);
		break;
	*/
	}
}

void Arkanoid::specialKeyboardDown(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		pedana.setMuovesx(true);
		break;
	case GLUT_KEY_RIGHT:
		pedana.setMuovedx(true);
		break;
	}
}

void Arkanoid::specialKeyboardUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		pedana.setMuovesx(false);
		break;
	case GLUT_KEY_RIGHT:
		pedana.setMuovedx(false);
		break;
	}
}
