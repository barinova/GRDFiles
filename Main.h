#include <glut.h> 
#include <windows.h>
#include <fstream>
#include <vector>

#pragma once

using namespace std;

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
	vector<vector<double>> pointsGRD;
	bool ReadGRDFile(const char* fileName);
	void InitializePoints();
};

