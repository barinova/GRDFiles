#include "Main.h"


vector<std::vector<Point>> points;
int width, height;
int rows, columns;
bool isSaved;

CMain::CMain(const char *fileName)
{
	if (fileName)
	{
		//set BMPs size
		isSaved = false;
		width = 600;
		height = 400;
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
	SaveImage();
}

void SaveImage()
{
	// Make the BYTE array, factor of 3 because it's RBG.
	
	BYTE* pixels = new BYTE[ 3 * width * height];;
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, TRUE);
	FreeImage_Save(FIF_BMP, image, "C:/GRD.bmp", 0);



	// Free resources
	FreeImage_Unload(image);
	delete [] pixels;
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