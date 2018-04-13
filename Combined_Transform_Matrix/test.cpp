#include <GL/glut.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
float rc = 0, r1 = 0, r2 = 0;//旋转变换
float sc = 1, s1 = 1, s2 = 1;//缩放变换
float nc = 0.5, n1 = 0.5, n2 = 0.5;//缩放倍数
void init(void) {
	glEnable(GL_DEPTH_TEST);
}
void  keyboard(unsigned char key, int x, int y) {
	GLfloat mat[16];
	glMatrixMode(GL_MODELVIEW);
	switch (key)
	{
	case 'x':// X键控制两个三角形的共同旋转
	case 'X':
		rc += 5;
		glutPostRedisplay();
		break;
	case 'w'://W键控制第一个三角形的旋转
	case 'W':
		r1 += 5;
		glutPostRedisplay();
		break;
	case 's'://S键控制第一个三角形的旋转
	case 'S':
		r2 += 5;
		glutPostRedisplay();
		break;
	case 'E'://E键控制第一个三角形的的缩放
	case 'e':
		if (s1 == 0.125)n1 = 2; //当缩小到1/8倍时，开始变大  
		if (s1 == 1) n1 = 0.5;//放大到原图时，开始缩小       
		s1 *= n1;
		glutPostRedisplay();
		break;
	case 'D'://D键控制第二个三角形的的缩放
	case 'd':
		if (s2 == 0.125)n2 = 2;
		if (s2 == 1) n2 = 0.5;
		s2 *= n2;
		glutPostRedisplay();
		break;
	case 'C'://C键控制两个三角形的共同缩放
	case 'c':
		if (sc == 0.125)nc = 2;
		if (sc == 1) nc = 0.5;
		sc *= nc;
		glutPostRedisplay();
		break;
	case '/e': //按ESC退出
		exit(0);
	default: //恢复至初始形状
		rc = 0; r1 = 0; r2 = 0;//旋转变换
		sc = 1; s1 = 1; s2 = 1;//缩放变换
		nc = 0.5; n1 = 0.5; n2 = 0.5;//缩放倍数
		glutPostRedisplay();
		break;
	}
}
void drawTri(int no) {  //三角形顶点信息
	if (no == 1) { //第一个三角形
		glBegin(GL_TRIANGLES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(-1,0, 0);
			glVertex3f(0, -1, 0.0);
		glEnd();
	}
	if (no == 2) { //第一个三角形
		glBegin(GL_TRIANGLES);
			glColor3f(0, 1, 0);
			glVertex3f(1, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, -1, 0.0);
		glEnd();
	}
}
void display(void) {

	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	/*共同变换*/
	glRotatef(rc, 0, 0, 1);
	glScalef(sc, sc, sc);

	/*第一个三角形变换*/
	glPushMatrix();
	glRotatef(r1, 0, 0, 1);
	glScalef(s1, s1, s1);
	drawTri(1);

	/*第二个三角形变换*/
	glPopMatrix();
	glRotatef(r2, 0, 0, 1);
	glScalef(s2,s2,s2);
	drawTri(2);

	glFlush();
}
void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Triangle");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}