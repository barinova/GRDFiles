#include "Main.h"

int rows, columns;
double xMin, xMax, yMin, yMax, zMin, zMax;
vector<std::vector<Point>> points;

CMain::CMain(const char *fileName)
{
	if (fileName)
	{
		if (ReadGRDFile(fileName))
		{
			InitializePoints();
		}
	}
}


CMain::~CMain(void)
{
}

bool CMain::ReadGRDFile(const char *fileName)
{
	std::ifstream GDRFile(fileName);
	double value;

	if (GDRFile) 
	{
        GDRFile.ignore(256, '\n');
		GDRFile >> columns >> rows;
        GDRFile >> xMin >> xMax >> yMin >> yMax >> zMin >> zMax;
		 
		if (rows > 0 && columns > 0)
		{
			pointsGRD.resize(rows);

			for (int i(0); i < rows; i++)
			{
				pointsGRD[i].resize(columns);

				for (int j(0); j < columns; j++)
				{
					GDRFile >> value;
					pointsGRD[i][j] = value;

				}
			}
			return true;
		}
	}
		return false;
}

void CMain::InitializePoints()
{
	double diff, element;
	diff = zMax - zMin;
	for (int i(0); i < rows; i++)
    {
		points.resize(columns);

		for (int j(0); j < columns; j++)
        {
			Point pt;
			element = pointsGRD[i][j];

			pt.x = i;
			pt.y = j;
			pt.r = (element - zMin)/diff*255;
			pt.b = (element - zMin)/diff*255;
			pt.g = (element - zMin)/diff*255;

			points[i].push_back(pt);
		} 
	}
}

void Draw()
{
	Point p;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	for (int i(0); i < rows; i++)
    {
        for (int j(0); j < columns; j++)
        {
			p = points[i][j];
			glColor3ub(p.r, p.g, p.b);
			glBegin(GL_POINTS);
			glVertex2f( - 0.5 + p.x/400, - 1 + p.y/400);
			glEnd();
		}
	  }
    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	CMain item("t001680.grd");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(640,480);
    glutCreateWindow("GRD");
	glutDisplayFunc(Draw);
	glutMainLoop();

    return 0;
}