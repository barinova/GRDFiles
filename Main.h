#include <glut.h> 
#include <windows.h>
#include <fstream>
#include <vector>
#include "Dist\FreeImage.h"
#pragma once

using namespace std;

void SaveImage();

struct Point
{
	double x, y;
    unsigned char r, g, b;
};

class CMain
{
public:
	CMain(const char *fileName);
	~CMain(void);
private:
	double xMin, xMax, yMin, yMax, zMin, zMax;
	vector<vector<double>> pointsGRD;
	bool ReadGRDFile(const char* fileName);
	void InitializePoints();
};

