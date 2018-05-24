#include <core/core.hpp>
#include <highgui/highgui.hpp>
#include <imgproc/imgproc.hpp>
#include <iostream>
#include <GL/glut.h>

using namespace std;
using namespace cv;

struct Vect
{
	GLfloat x, y, z;
};
struct terr_map{
	int rows;
	int cols;
	Vect *point;
};
terr_map mapdata(const string& filename);
Vect *Vertex_normal(terr_map map);