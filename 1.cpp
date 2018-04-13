#include <GL/glut.h>  

void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void setMatrix(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.0f, 0.1f);
	glVertex2f(-0.8f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.1f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.1f, 0.1f, 1.0f);
	glVertex2d(-1.0f, 0.9f);
	glEnd();
	glFlush();
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Èý½ÇÐÎ");

	glutDisplayFunc(Display);
	setMatrix();
	init();

	glutMainLoop();
	return 0;
}
