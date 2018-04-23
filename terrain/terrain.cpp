#include <GL/glut.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;
GLfloat lightx=0.0,lighty=0.0,lightz=150.0;
GLfloat lookatX=100.0,lookatY=0.0,lookatZ=100.0;
GLfloat scale=1.0;
struct Vec
{
	float x,y,z;
};
Vec data[100][200];
Vec Pvector[20];
//GLfloat X=0.0,Y=0.0,Z=0.0;
//读取顶点数据
void Data()
{
	ifstream infile("Vertexdata.dat",ios::in);
	if(!infile){
		cout << "open error!" << endl;
		exit(1);
	}
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 200; j++)
		{
			infile >> data[i][j].x >> data[i][j].y >> data[i][j].z;
		}
	}
	
}
//
Vec add(Vec a,Vec b,Vec c,Vec d,Vec e,Vec f)
{
	Vec sum = {a.x+b.x+c.x+d.x+e.x+f.x,a.y+b.y+c.y+d.y+e.y+f.y,a.z+b.z+c.z+d.z+e.z+f.z};
	return sum;
}

//
void normalvector()
{
	Vec Tvector[2][46];
	int vx=0,vy=0;
	for(int j =  1; j < 3; j++)
	{
		for(int i = 38; i <= 80; i++)
		{	
			if(i%2==0){
				Vec vec1 = {data[j][i].x - data[j][i+2].x,data[j][i].y - data[j][i+2].y,data[j][i].z - data[j][i+2].z};
				Vec vec2 = {data[j+1][i+1].x - data[j][i].x,data[j+1][i+1].y - data[j][i].y,data[j+1][i+1].z - data[j][i].z};
				Vec norm1 = {vec1.y*vec2.z - vec1.z*vec2.y,vec1.z*vec2.x - vec1.x*vec2.z,vec1.x*vec2.y - vec1.y*vec2.x};
				Tvector[vx][vy] = norm1;
				vy++;
			}
			else{
				Vec vec3 = {data[j+1][i+3].x - data[j+1][i+1].x,data[j+1][i+3].y - data[j+1][i+1].y,data[j+1][i+3].z - data[j+1][i+1].z};
				Vec vec4 = {data[j][i+2].x - data[j+1][i+3].x,data[j][i+2].y - data[j+1][i+3].y,data[j][i+2].z - data[j+1][i+3].z};
				Vec norm2 = {vec3.y*vec4.z - vec3.z*vec4.y,vec3.z*vec4.x - vec3.x*vec4.z,vec3.x*vec4.y - vec3.y*vec4.x};
				Tvector[vx][vy] = norm2;
				vy++;
			}
		}
		vy=0;
		vx++;
	}
	int a = 0, b = 0;
	for(int i = 0; i < 20; i++)
	{
		Vec norm = add(Tvector[b][a+1],Tvector[b][a+2],Tvector[b][a+3],Tvector[b+1][a],Tvector[b+1][a+1],Tvector[b+1][a+2]);
		float l=sqrt(norm.x*norm.x+norm.y*norm.y+norm.z*norm.z);
		Pvector[i].x = norm.x / l;
		Pvector[i].y = norm.y / l;
		Pvector[i].z = norm.z / l;
		a+=2;
	}

}
//初始化
void init()
{

	glShadeModel(GL_SMOOTH);
	glClearColor(0.7f,0.7f,0.7f,0.0f);
	glEnable(GL_DEPTH_TEST);
}
//绘制图形
void drawTrangle()
{
	for(int i = 0; i < 100; i++)
	{	
		int nm=0;
		glColor3f(0.0,1.0,0.2);
		glBegin(GL_TRIANGLE_STRIP);
			for(int j = 0; j < 200; j+=2)
			{	
				glNormal3f(Pvector[nm].x,Pvector[nm].y,Pvector[nm].z);
				glVertex3f(data[i][j].x,data[i][j].y,data[i][j].z);
				glNormal3f(Pvector[nm].x,Pvector[nm].y,Pvector[nm].z);
				glVertex3f(data[i][j+1].x,data[i][j+1].y,data[i][j+1].z);
				nm+=1;
				if(nm==20)
					nm=1;
			}
		glEnd();
	}
}
//键盘
void keyboard(int key,int x,int y)
{
	int mode;
	switch(key)
	{
		case GLUT_KEY_LEFT:
			mode=glutGetModifiers();
			if(mode==GLUT_ACTIVE_CTRL) 	
			{	if(lookatY>-150.0)
					lookatY-=5.0;
			}
			else
			{
				if(lighty>-50.0)
					lighty-=5.0;
			}
			break;
		case GLUT_KEY_RIGHT:
			mode=glutGetModifiers();
			if(mode==GLUT_ACTIVE_CTRL) 	
			{	if(lookatY<150.0)
					lookatY+=5.0;
			}
			else
			{
				if(lighty<250.0)
					lighty+=5.0;
			}
			break;
		case GLUT_KEY_UP:
			mode=glutGetModifiers();
			if(mode==GLUT_ACTIVE_CTRL) 	
			{
				if(lookatZ<150.0)
					lookatZ+=5.0;
			}
			else
			{
				if(lightx<150.0)
					lightx+=5.0;
			}
			break;
		case GLUT_KEY_DOWN:
			mode=glutGetModifiers();
			if(mode==GLUT_ACTIVE_CTRL) 	
			{
				if(lookatZ>-150.0)
					lookatZ-=5.0;
			}
			else
			{
				if(lightx>-150.0)
					lightx-=5.0;
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
	return;
}

void mouse(int button,int state,int x,int y)
{
	if(button == GLUT_WHEEL_UP)
	{
		scale+=0.01;
		glutPostRedisplay();
	}
	else if(button == GLUT_WHEEL_DOWN)
	{
		scale-=0.01;
		glutPostRedisplay();
	}
}
//窗口改变时的回调函数
void ChangeSize(GLint w,GLint h)
{
	GLfloat ratio;//横宽比
	GLfloat coordinatesize = 100.0f;//设置坐标系
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ratio = (GLfloat)w/(GLfloat)h;
	glOrtho(-coordinatesize,coordinatesize,-coordinatesize,coordinatesize,-coordinatesize*2.5,coordinatesize*2.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	GLfloat light_position[]={lightx,lighty,lightz,0.0};
	cout << lightx <<" "<< lighty << " " << lightz << endl;
	//GLfloat light_ambient[]={0.0,0.0,0.0,1.0};
	GLfloat light_diffuse[]={1.0,1.0,1.0,1.0};
	GLfloat light_specular[]={0.5,0.5,0.5,1.0};
	GLfloat diffuse[]={0.6,0.0,0.0,1.0};
	glLoadIdentity();
	glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	//glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	//gluPerspective(130.0,(GLfloat)w/(GLfloat)h,2.0,300.0);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	gluLookAt(lookatX,lookatY,lookatZ,0.0,0.0,0.0,0.0,0.0,1.0);
	glScalef(scale,scale,scale);
	drawTrangle();
//glPopMatrix();
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(200,200);
	glutCreateWindow("...");
	Data();
	normalvector();
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}
