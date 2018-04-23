#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	float a[60000];
	float x = -50.0f;
	float y = -50.0f;
	float z = 0.0f;
	ofstream outfile("Vertexdata.dat",ios::out);
	if(!outfile)
	{
		cout<<"open erroe!"<<endl;
		exit(1);
	}
	for(int j = 0; j <100; j++)
	{
		for(int i = 0; i < 100; i++)
		{
			
			outfile << x <<" ";
			outfile << y <<" ";
			outfile << cos(i*M_PI/10)*4 << endl;
			outfile << x+1 << " ";
			outfile << y << " ";
			outfile << cos(i*M_PI/10)*4 << endl;
			y+=1;
		}
		y=-50;
		x+=1;
	}
	outfile.close();
	
	ifstream infile("Vertexdata.dat",ios::in);
	if(!infile)
	{
		cout << "open error!" <<endl;
		exit(1);
	}
	for(int i=0; i<60000; i+=3)
	{
		infile >> a[i] >> a[i+1] >> a[i+2];
		cout << a[i] << " " << a[i+1] << " " << a[i+2] << endl;
	}
	infile.close();
	return 0;
}
