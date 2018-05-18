#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

struct Vec
{
	float x,y,z;
};
Vec vertex[103][103][2];
Vec tnorl[102][204];
//
void setpoint()
{
	float x = -51.0f;
	float y = -51.0f;
	float z = 0.0f;
	for(int j = 0; j <103; j++)
	{
		for(int i = 0; i < 103; i++)
		{
			vertex[j][i][0].x = x;
			vertex[j][i][0].y = y;
			if(cos(i*M_PI/10) < 0 || cos(x*M_PI/10)<0)
				vertex[j][i][0].z = cos(i*M_PI/10)*((-(y*y)+2500)/900)*((-(x*x)+2500)/900)*cos(x*M_PI/10);
			else
				vertex[j][i][0].z = cos(i*M_PI/10)*((-(y*y)+2500)/900)*((-(x*x)+2500)/900)*cos(x*M_PI/10);
			/*outfile << x <<" ";
			outfile << y <<" ";
			outfile << cos(i*M_PI/10)*8 << endl;
			outfile << x+1 << " ";
			outfile << y << " ";
			outfile << cos(i*M_PI/10)*8 << endl;*/
			y++;
		}
		y=-51;
		x++;
	}
}

Vec add(Vec a,Vec b,Vec c,Vec d,Vec e,Vec f)
{
	Vec sum = {a.x+b.x+c.x+d.x+e.x+f.x,a.y+b.y+c.y+d.y+e.y+f.y,a.z+b.z+c.z+d.z+e.z+f.z};
	return sum;
}

Vec Tnorl(Vec a,Vec b,Vec c)
{
	Vec value1,value2,norl;
	value1.x = a.x-b.x;
	value1.y = a.y-b.y;
	value1.z = a.z-b.z;
	value2.x = b.x-c.x;
	value2.y = b.y-c.y;
	value2.z = b.z-c.z;
	norl.x = value2.y*value1.z - value2.z*value1.y;
	norl.y = value2.z*value1.x - value2.x*value1.z;
	norl.z = value2.x*value1.y - value2.y*value1.x;
	return norl;
}
//
void Triangle_normal()
{
	for (int i = 0; i < 102; i++) {
		/* code */
		for (int j = 0; j < 102; j++) {
			/* code */
				int t = j*2;
				tnorl[i][t] = Tnorl(vertex[i+1][j][0],vertex[i][j][0],vertex[i][j+1][0]);
				tnorl[i][t+1] = Tnorl(vertex[i][j+1][0],vertex[i+1][j+1][0],vertex[i+1][j][0]);
		}
	}
}

void Vertex_normal()
{
	for (int i = 1; i < 102; i++){
		for (int j = 1; j < 102; j++){
			Vec norl = add(tnorl[i-1][j*2-1],tnorl[i-1][j*2],tnorl[i-1][j*2+1],tnorl[i][j*2-2],tnorl[i][j*2-1],tnorl[i][j*2]);
			float l = sqrt(norl.x*norl.x+norl.y*norl.y+norl.z*norl.z);
			vertex[i][j][1].x = norl.x/l;
			vertex[i][j][1].y = norl.y/l;
			vertex[i][j][1].z = norl.z/l;
		}
	}

}


void outputfile(){
	ofstream outfile("Vertexdata.dat",ios::out);
	if(!outfile)
	{
		cout<<"open erroe!"<<endl;
		exit(1);
	}
	for(int i = 1; i < 102; i++){
		for(int j = 1; j < 102; j++){
			outfile << vertex[i][j][0].x << " " << vertex[i][j][0].y << " " << vertex[i][j][0].z << " " << vertex[i][j][1].x << " " << vertex[i][j][1].y << " " << vertex[i][j][1].z << endl;
		}
	}
	outfile.close();
	ifstream infile("Vertexdata.dat",ios::in);
	if(!infile)
	{
		cout << "open error!" <<endl;
		exit(1);
	}
	for(int i = 0; i < 10201; i++)
	{	
		float a,b,c,d,e,f;
		infile >> a >> b >> c >> d >> e >> f;
		cout << i << ":    " << a << " " << b << " " << c << " " << d << " " << e << " " << f << endl;
	}
	infile.close();
}

int main()
{
	setpoint();
	Triangle_normal();
	Vertex_normal();
	outputfile();
	return 0;
}
