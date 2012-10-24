#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./3Dcurve.h"
#include "./cube.h"

void drawR()
{
	glPushMatrix();
		glTranslatef(0.5, -3, 0);
		glPushMatrix();
		glScalef(1, 6, 1);
		//1
		cube();
		glPopMatrix();
		glPushMatrix();
			glRotatef(270, 0, 0, 1);
			glTranslatef(-1,0.5,0);
			//2
			draw3Dcurve(1, 1.0, 2.0, 0.0, 180, 5);
			glTranslatef(3,0,0);
			//3
			draw3Dcurve(1, 1, 2, 90, 180, 5);
			glTranslatef(0.5, 1.5, 0);
			//4
			cube();
		glPopMatrix();
	glPopMatrix();
}
