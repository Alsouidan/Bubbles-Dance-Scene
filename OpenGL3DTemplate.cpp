#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <glut.h>
#include <Windows.h>
#include <MMSystem.h>
using namespace std;
int counter = 0;
int slowFactor = 1;
int counter2 = 0;
float rotation = 0;
int flag = 0;
bool headFlag = true;
float znear = 0.1;
float eyeX = 0;
float eyeY = 0;
float eyeZ = 0;
float centerX = 0;
float centerY = 0;
float centerZ = -200;
float upY = 1;
float fovy = 45;
float r1 = 1;
float b1 = 0;
float g1 = 0;
float r2 = 0;
float b2 = 1;
float g2 = 0;
float r3 = 0;
float b3 = 0;
float g3 = 1;
float r4 = 1;
float b4 = 0;
float g4 = 1;
float r5 = 0;
float b5 = 1;
float g5 = 1;
float rotateHead = 0;
float hands = 0;
float headX = 0;
float headY = 0;
float bubbleX = 0;
float rightLeg = 0;
float leftLeg = 0;
bool rightFlag = true;
float hand2 = 0;
float bubbleY = 0;
bool fly = true;




void initGL() {
	glClearColor(0, 0, 0, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case't':eyeY = 1.5;
		eyeZ = -4.5;
		fovy = 47;
		centerY = -390.5;
		break;
	case 'w':eyeY += 0.05;break;
	case 's':eyeY -= 0.05;break;
	case '=': //zoom
		fovy += 2;
		break;
	case'-':fovy -= 2;
		break;
	case 'e': //normal
		centerY += 0.5;
		break;
	case 'q': //up
		centerY -= 0.5;
		//centerZ++;
		//centerY++;
		break;
	case 'a':eyeZ += 0.3;break;
	case 'd':eyeZ -= 0.3;break;
	case 'l':eyeY =0;
		eyeZ = 0;
		fovy = 45;
		centerY = 0;
		break;
	case'r':slowFactor = (slowFactor==4)?1:4;break;

	}
	glutPostRedisplay();
}
void setupCamera() {
	GLfloat aspect = (GLfloat)1000 / (GLfloat)700;
	//glViewport(0, 0, 1000, 700);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, znear, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, eyeY, eyeZ, centerX, centerY, centerZ, 0, 1, 0);
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void display() {
	//setupLights();
	setupCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslatef(0, 0.0f, -6.0f);
	//room
	glPushMatrix();
	glScaled(3.5, 3, 3.5);
	//base
	glPushMatrix();
	glColor3f(r1, g1, b1);
	glTranslated(0, -0.5, 0);
	glScaled(1, 0.02, 1);
	glutSolidCube(1);
	glPopMatrix();
	//top
	glPushMatrix();
	glColor3f(r2, g2, b2);
	glTranslated(0, 0.5, 0);
	glScaled(1, 0.02, 1);
	glutSolidCube(1);
	glPopMatrix();
	//center
	glPushMatrix();
	glColor3f(r3, g3, b3);
	glRotated(90, 1, 0, 0);
	glScaled(1, 0.02, 1);
	glutSolidCube(1);
	glPopMatrix();
	// right
	glPushMatrix();
	glColor3f(r4, g4, b4);
	glTranslated(0.5, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScaled(1, 0.02, 1);
	glutSolidCube(1);
	glPopMatrix();
	// left
	glPushMatrix();
	glColor3f(r5, g5, b5);
	glTranslated(-0.5, 0, 0);
	glRotated(-90, 0, 0, 1);
	glScaled(1, 0.02, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	//bubblezzzzzzzz
	glTranslated(bubbleX, -0.75+bubbleY, 0.75);
	glScaled(0.3, 0.3, 0.3);

	//head
	glPushMatrix();
	glRotated(rotateHead, 0, 1, 0);
	glTranslated(headX,headY,0);
	//hair
	glPushMatrix();
	glColor3f(0.8, 0.7, 0);
	glTranslated(0, 0.6, -0.5);
	glScaled(1.5, 0.85, 1.2);
	glutSolidSphere(1.2, 150, 50);
	glTranslated(1.2, 0, 0.4);
	glScaled(0.5 / 1.5, 0.6 / 0.85, 0.5 / 1.2);
	glutSolidSphere(1.2, 150, 50);
	glScaled(1 / (0.5 / 1.5), 1 / (0.6 / 0.85), 1 / (0.5 / 1.2));
	glTranslated(-0.77*1.5 / 0.5, -0.05*0.85 / 0.6, 0);
	glScaled(0.5 / 1.5, 0.6 / 0.85, 0.5 / 1.2);
	glutSolidSphere(1.2, 150, 50);
	glPopMatrix();
	//face
	glPushMatrix();
	glColor3f(1, 0.8, 0.64);
	glScaled(1.5, 1, 1);
	glutSolidSphere(1, 150, 50);
	glTranslated(10, 0, 0);
	glPopMatrix();
	//outer eye
	glPushMatrix();
	glTranslated(-0.6, 0, 0.7);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.5, 50, 50);
	glTranslated(1.2, 0, 0);
	glutSolidSphere(0.5, 50, 50);
	//inner eye
	glPushMatrix();
	glTranslated(-1.2, 0, 0.5);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.2, 50, 50);
	glTranslated(1.2, 0, 0);
	glutSolidSphere(0.2, 50, 50);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//body
	glPushMatrix();
	glRotated(rotation, 0, 0, 1);
	//1
	glPushMatrix();
	glColor3f(0.2, 0.7, 0.9);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.1, 0.5, 1.2, 50, 50);
	glPopMatrix();
	//2
	glPushMatrix();
	glTranslated(0, -1.2, 0);
	glColor3f(0, 0, 0);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.5, 0.6, 0.3, 50, 50);
	glPopMatrix();
	//3
	glPushMatrix();
	glTranslated(0, -1.5, 0);
	glColor3f(0.2, 0.7, 0.9);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.6, 0.7, 0.3, 50, 50);
	glPopMatrix();
	//legs
	glPushMatrix();
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.3, -1.8, 0);
	glScaled(0.2, 2.5, 0.2);
	glRotated(90, 1, 0, 0);
	glTranslated(0, 0, 0);
	gluCylinder(gluNewQuadric(), 0.7, 0.7, 0.2, 50, 50);
	glTranslated(3, 0, 0);
	gluCylinder(gluNewQuadric(), 0.7, 0.7, 0.2, 50, 50);
	glPopMatrix();
	glTranslated(-0.3, -2.2, 0);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.15, 50, 50);
	glTranslated(0.6, 0, 0);
	glutSolidSphere(0.15, 50, 50);
	glPopMatrix();
	//hands
	glPushMatrix();
	glTranslated(-0.8, -1.3, 0);
	glRotated(-40, 0, 0, 1);
	glRotated(-hands+hand2, 0, 0, 1);
	glColor3f(1, 0.8, 0.64);
	glScaled(0.2, 0.5, 0.2);
	glutSolidSphere(1, 150, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.8, -1.3, 0);
	glRotated(40, 0, 0, 1);
	glRotated(hands, 0, 0, 1);
	glColor3f(1, 0.8, 0.64);
	glScaled(0.2, 0.5, 0.2);
	glutSolidSphere(1, 150, 50);
	glPopMatrix();
	glPopMatrix();
	glFlush();
}
void timer(int value) {

	r1 = (rand() % 10)*0.1;
	b1 = (rand() % 10)*0.1;
	g1 = (rand() % 10)*0.1;
	r2 = (rand() % 10)*0.1;
	b2 = (rand() % 10)*0.1;
	g2 = (rand() % 10)*0.1;
	r3 = (rand() % 10)*0.1;
	b3 = (rand() % 10)*0.1;
	g3 = (rand() % 10)*0.1;
	r4 = (rand() % 10)*0.1;
	b4 = (rand() % 10)*0.1;
	g4 = (rand() % 10)*0.1;
	r5 = (rand() % 10)*0.1;
	b5 = (rand() % 10)*0.1;
	g5 = (rand() % 10)*0.1;

	glutPostRedisplay();
	glutTimerFunc(500 * slowFactor, timer, 0);
}

void dance(int value) {
	if (counter % 40 == 0) { flag = (flag==2)?0:flag+1; 
	 rotateHead = 0;
	 hands = 0;
	 headX = 0;
	 headY = 0;
	 bubbleX = 0;
	 rightLeg = 0;
	 leftLeg = 0;
	 rightFlag = true;
	 rotation = 0;
	 hand2 = 0;
	 bubbleY = 0;
	 fly = true;
	}
	if (flag==0) {
		if (rotateHead >= 0) {
			rotateHead = -45;
			hands = 60;
		}

		else {
			rotateHead = 45;
			hands = 90;
		}
		if (hands == abs(40)) {

		}
	}

	counter++;
	glutPostRedisplay();
	glutTimerFunc(500 * slowFactor, dance, 0);
}
void danceTwo(int value) {
	if (flag==1) {
	counter2++;
	if (rightFlag &&counter2 %4==0) {
		rightLeg = 0.2;
		leftLeg = 0;
		rightFlag = !rightFlag;
	}
	else if(counter2 % 4 == 0)
	{
		rightLeg = 0;
		leftLeg = 0.2;
		rightFlag = !rightFlag;

	}
	
		if (headFlag) {
			headX += 0.01;
			headY = -0.2;
			bubbleX += 0.015;
			rotation += 0.5;
		}
		else {
			headY = 0;
			headX -= 0.01;
			bubbleX -= 0.015;
			rotation -= 0.5;


		}
		cout << headX << endl;
		if (headX == 0 || headX>=0.5 ||headX<=-0.5) {
			headFlag = !headFlag;
		}
		
	}
	glutPostRedisplay();
	glutTimerFunc(50 * slowFactor, danceTwo, 0);
}
void dance3(int value) {
	if (flag == 2) {
		hand2 = 70;
		if (fly) {
			bubbleY += 0.01;
		}
		else {
			bubbleY -= 0.01;
		}
		if (bubbleY >= 0.3 ||bubbleY<=0) {
			fly = !fly;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(50 * slowFactor, dance3, 0);
}
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {


	glutInit(&argc, argv);

	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("character");
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	PlaySound(TEXT("song1.wav"), NULL, SND_ASYNC);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glutTimerFunc(500*slowFactor, dance, 0);
	glutTimerFunc(50 * slowFactor, danceTwo, 0);
	glutTimerFunc(50 * slowFactor, dance3, 0);
	glutTimerFunc(500 * slowFactor, timer, 0);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return 0;
}