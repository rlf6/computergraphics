#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./3Dcurve.h"
#include "./cube.h"

void drawL()
{
	glPushMatrix();
		glTranslatef(0, -2, 0);
		glPushMatrix();
			glScalef(1,4,1);
			//1
			cube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.5, -2, 0);
			//2
			draw3Dcurve(1, 1, 2, 180, 270, 5);
			glTranslatef(0.5, -1.5, 0);
			//3
			cube();
		glPopMatrix();
	glPopMatrix();
}
