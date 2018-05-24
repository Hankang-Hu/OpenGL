#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "SOIL.h"
#include "mygl.h"

using namespace std;

GLfloat lightx = 0.0, lighty = 0.0, lightz = 50.0, spotx = 0.0, spoty = 0.0, spotz = 50.0;
GLfloat lookatX = 100.0, lookatY = 0.0, lookatZ = 100.0, lookcenterX = 0.0, lookcenterY = 0.0, lookcenterZ = 0.0, topX = 0.0, topY = 0.0, topZ = 100.0;
GLfloat scale = 1.0;
GLfloat angle = 0.0, R;
terr_map terrmap;
Vect *normal;
unsigned int texture;
//GLfloat X=0.0,Y=0.0,Z=0.0

//键盘
void keyboard(int key, int x, int y)
{
	int mode;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		mode = glutGetModifiers();
		if (mode == GLUT_ACTIVE_CTRL)
		{
			angle -= 3.0;
		}
		else
		{
			if (lighty > -100.0)
				lighty -= 2.0;
		}
		break;
	case GLUT_KEY_RIGHT:
		mode = glutGetModifiers();
		if (mode == GLUT_ACTIVE_CTRL)
		{
			angle += 3.0;
		}
		else
		{
			if (lighty < 100.0)
				lighty += 2.0;
		}
		break;
	case GLUT_KEY_UP:
		mode = glutGetModifiers();
		if (mode == GLUT_ACTIVE_CTRL)
		{
			if (lookatZ < 200.0)
				lookatZ += 2.0;
		}
		else
		{
			if (lightx > -100.0)
				lightx -= 2.0;
		}
		break;
	case GLUT_KEY_DOWN:
		mode = glutGetModifiers();
		if (mode == GLUT_ACTIVE_CTRL)
		{
			if (lookatZ > -100.0)
				lookatZ -= 2.0;
		}
		else
		{
			if (lightx < 100.0)
				lightx += 2.0;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	return;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_WHEEL_DOWN)
{
	scale += 0.05;
	glutPostRedisplay();
}
else if (button == GLUT_WHEEL_UP)
{
	scale -= 0.05;
	glutPostRedisplay();
}
}

//窗口改变时的回调函数
void ChangeSize(GLint w, GLint h)
{
	//GLfloat ratio;//横宽比
	GLfloat coordinatesize = 100.0f;//设置坐标系
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0, (GLfloat)w / (GLfloat)h, 1.0, 300.0);
	//ratio = (GLfloat)w/(GLfloat)h;
	//glOrtho(-coordinatesize,coordinatesize,-coordinatesize,coordinatesize,-coordinatesize*2.5,coordinatesize*2.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void makedata()
{
	terrmap = mapdata("terrain.jpg");
	normal = Vertex_normal(terrmap);
}

//初始化

int loadtexture()
{
	int status = 1;
	texture = SOIL_load_OGL_texture(
		"texture.jpg", 
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y);
	if (texture == 0)
		status = 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return status;
}

void init()
{
	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	if (!loadtexture()){ cout << "load texture default!"<<endl; }
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}
//绘制图形
void drawTrangle()
{
	int x = terrmap.rows, y = terrmap.cols;
	glBindTexture(GL_TEXTURE_2D, texture);
	for (int i = 0; i < x-1; i++)
	{
		float ix = i;
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < y; j++){
			float jx = j;
			glNormal3f(normal[i*y + j].x, normal[i*y +j].y, normal[i*y + j].z);
			//cout << normal[i*y + j].x <<" "<< normal[i*y + j].y << " " << normal[i*y + j].z<<endl;
			glTexCoord2f(terrmap.point[i*y + j].x/10 , terrmap.point[i*y + j].y/10);
			glVertex3f(terrmap.point[i*y + j].x, terrmap.point[i*y + j].y, terrmap.point[i*y + j].z);
			glNormal3f(normal[(i+1)*y + j].x, normal[(i+1)*y + j].y, normal[(i+1)*y + j].z);
			glTexCoord2f(terrmap.point[(i + 1)*y + j].x/10, terrmap.point[(i + 1)*y + j].y/10);
			glVertex3f(terrmap.point[(i+1)*y + j].x, terrmap.point[(i+1)*y + j].y, terrmap.point[(i+1)*y + j].z);
		}
		glEnd();
	}
}

void light()
{
	GLfloat light_position[] = { lightx, lighty, lightz, 0.0 };
	//cout << lightx <<" "<< lighty << " " << lightz << endl;
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat M_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, M_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}
/*
void spot_light()
{
	GLfloat position[] = { spotx, spoty, spotz, 1.0 };
	GLfloat diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	GLfloat specular[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat direction[] = { 0.0, 0.0, -1.0 };
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.6);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}
*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//light();
	//spot_light();
	R = sqrt(lookatX*lookatX + lookatY*lookatY);
	gluLookAt(R*cos(M_PI / 180 * angle)*scale, R*sin(M_PI / 180 * angle)*scale, lookatZ*scale, lookcenterX, lookcenterY, lookcenterZ, topX, topY, topZ);
	light();
	//spot_light();
	//glutSolidCone(M_PI/180*angle*60.0,60.0,100,100);
	//cout << lookatX <<" "<< lookatY << " " << lookatZ << " " << topZ << endl;
	//glScalef(scale,scale,scale);
	drawTrangle();
	//glPopMatrix();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("...");
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	makedata();
	init();
	glutMainLoop();
	return 0;
}