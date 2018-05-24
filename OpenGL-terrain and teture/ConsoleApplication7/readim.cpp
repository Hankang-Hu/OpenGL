#include "mygl.h"


terr_map mapdata(const string& filename)
{
	terr_map map_point;
	Mat srcImage = imread(filename, IMREAD_GRAYSCALE);
	if (srcImage.empty())
	{
		cout << "File not exist!" << endl;
		exit(1);
	}
	Mat aimage;
	Mat image;
	//Mat image = srcImage;
	blur(srcImage, aimage, Size(3, 3), Point(-1, -1));
	//medianBlur(aimage, image, 5);
	//GaussianBlur(srcImage, aimage, Size(3, 3), 0, 0);
	bilateralFilter(srcImage, image, 25, 25 * 2, 25 / 2);
	//int a = image.channels();
	//namedWindow("image");
	//imshow("image",image);
	Vect *point = new Vect[image.rows*image.cols];
	int x = -image.rows / 2;
	int y = -image.cols / 2;
	float rx = image.rows, ry = image.cols;
	for (int i = 0; i < rx; i++)
	{
		for (int j = 0; j < ry; j++)
		{
			point[i*image.cols + j].x = x*100/rx;
			point[i*image.cols + j].y = y*100/rx;
			point[i*image.cols+j].z = (float)image.at<uchar>(i, j)*20/255;
			y++;
		}
		y = -image.cols / 2;
		x++;
	}
	map_point.point = point;
	map_point.rows = image.rows;
	map_point.cols = image.cols;
	/*
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << map_point.point[i*map_point.cols + j].x << "   " << map_point.point[i*map_point.cols + j].y << "   " << map_point.point[i*map_point.cols+j].z<<endl;
		}
	}
	*/
	return map_point;
}


Vect add(Vect a, Vect b, Vect c, Vect d, Vect e, Vect f)
{
	Vect sum = { a.x + b.x + c.x + d.x + e.x + f.x, a.y + b.y + c.y + d.y + e.y + f.y, a.z + b.z + c.z + d.z + e.z + f.z };
	return sum;
}

Vect Tnorl(Vect a, Vect b, Vect c)
{
	Vect value1, value2, norl;
	value1.x = a.x - b.x;
	value1.y = a.y - b.y;
	value1.z = a.z - b.z;
	value2.x = b.x - c.x;  
	value2.y = b.y - c.y;
	value2.z = b.z - c.z;
	norl.x = value2.y*value1.z - value2.z*value1.y;
	norl.y = value2.z*value1.x - value2.x*value1.z;
	norl.z = value2.x*value1.y - value2.y*value1.x;
	return norl;
}


Vect *Vertex_normal(terr_map map)
{
	int x = map.rows, y = map.cols;
	Vect *normal = new Vect[x*y];
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			if (i == 0 || j == 0 || i == x - 1 || j == y - 1)
			{
				normal[i*y + j].x = 0;
				normal[i*y + j].y = 0;
				normal[i*y + j].z = 1;
			}
			else
			{
				Vect norl = add(Tnorl(map.point[(i-1)*y + j], map.point[i*y + j], map.point[i*y + j-1]),
					Tnorl(map.point[i*y + j], map.point[(i-1)*y + j], map.point[(i-1)*y + j + 1]),
					Tnorl(map.point[(i-1)*y + j + 1], map.point[i*y + j + 1], map.point[i*y + j]),
					Tnorl(map.point[(i + 1)*y + j - 1], map.point[i*y + j - 1], map.point[i*y + j]),
					Tnorl(map.point[i*y + j], map.point[(i + 1)*y + j], map.point[(i + 1)*y + j - 1]),
					Tnorl(map.point[(i + 1)*y + j], map.point[i*y + j], map.point[i*y + j + 1]));
				float l = sqrt(norl.x*norl.x + norl.y*norl.y + norl.z*norl.z);
				normal[i*y + j].x = norl.x /l;
				normal[i*y + j].y = norl.y /l;
				normal[i*y + j].z = norl.z /l;
			}
		}
	}
	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << normal[i*x + j].x << "   " << normal[i*x + j].y << "   " << normal[i*x + j].z << endl;
		}
	}
	*/
	return normal;
}