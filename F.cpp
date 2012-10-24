#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./3Dcurve.h"
#include "./cube.h"

void drawF()
{
	glPushMatrix();
		glTranslatef(2, -2, 0);
		//1
		draw3Dcurve(1, 1, 2, 90, 180, 5); 
		glTranslatef(-1.5, -2, 0);
		glPushMatrix();
			glScalef(1, 4, 1);
			//2
			cube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2, 3.5, 0);
			//3
			cube();
			glTranslatef(-0.5, -3, 0);
			glScalef(2, 1, 1);
			//4
			cube();
		glPopMatrix();
	glPopMatrix();
}
