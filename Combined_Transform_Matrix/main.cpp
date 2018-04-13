
#include <GL/glut.h>
#include <math.h>

using namespace std;
GLfloat triangle1=0.0,triangle2=0.0,scale=1,global=0.0;
void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f,1.0f,1.0f,0.0f);
}

//
void drawTriangle1()
{
	glPushMatrix();
	glRotatef(triangle1,0.0f,0.0f,-1.0f);
	glScalef(scale,scale,scale);
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(-90.0f,0.0f);
		glVertex2f(0.0f,15.0f);
		glVertex2f(0.0f,-15.0f);
		glVertex2f(90.0f,0.0f);

	glEnd();
	glPopMatrix();
}
void drawTriangle2()
{
	glPushMatrix();
	glRotatef(triangle2,0.0f,0.0f,-1.0f);
	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(0.0f,90.0f);
		glVertex2f(15.0f,0.0f);
		glVertex2f(-15.0f,0.0f);
		glVertex2f(0.0f,-90.0f);
	glEnd();
	glPopMatrix();
}
void drawCenter()
{
	int n=100;
	GLfloat R=18.3f;
	GLfloat pi=3.1415926f;
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < n; i++)  
    {
        glVertex2f(R*cos(2*pi/n*i), R*sin(2*pi/n*i));
    }
    glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	//
	glScalef(scale,scale,scale);
	glRotatef(global,0.0,0.0,-1.0);
	drawTriangle1();
	drawTriangle2();
	drawCenter();
	glFlush();
}
void Keyboard(int key,int x,int y)
{
	int mode;
	switch(key)
	{
		case GLUT_KEY_LEFT:
			mode=glutGetModifiers();
			if(mode == GLUT_ACTIVE_CTRL)
			{
				triangle2=triangle2-6;
			}
			else
			{	
				triangle1=triangle1-6;
			}
			break;
		case GLUT_KEY_RIGHT:
			mode=glutGetModifiers();
			if(mode == GLUT_ACTIVE_CTRL)
			{
				triangle2=triangle2+6;
			}
			else
			{	
				triangle1=triangle1+6;
			}
			break;
		case GLUT_KEY_UP:
			if(scale<1.5){
				scale=scale+0.1;
			}
			break;
		case GLUT_KEY_DOWN:
			if(scale>0.3){
				scale=scale-0.1;
			}
			break;
		case GLUT_KEY_PAGE_UP:
			global=global+6;
			break;
		case GLUT_KEY_PAGE_DOWN:
			global=global-6;
			break;
		default:  
        	break;
	}
	glutPostRedisplay();
	return;
}
//glutPostRedisplay(); 
void ChangeSize(int w,int h)  
{  
    if (h == 0)  
        h = 1;  
    glViewport(0,0,w,h);  
  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    //设置裁剪空间  
    if (w <= h)  
        glOrtho(-100.0f, 100.0f, -100.0f*h/w, 100.0f*h/w, -100.0f, 100.0f);  
    else  
        glOrtho(-100.0f*w/h, 100.0f*w/h, -100.0f, 100.0f, -100.0f, 100.0f);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("...");

	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(Keyboard);
	init();
	
	glutMainLoop();
	return 0;
}