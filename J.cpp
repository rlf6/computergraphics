#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./3Dcurve.h"
#include "./cube.h"

void drawJ()
{
	glTranslatef(0, -4, 0);
	glPushMatrix();
		//Draw curve using code in 3DCurve.cpp
		
	glPopMatrix();
	glPushMatrix();
		glScalef(4.0,1.0,1.0);
		glTranslatef(0.5,3.5,0.0);
		cube();
	glPopMatrix();
	glPushMatrix();
		glScalef(1.0,4.0,1.0);
		glTranslatef(2.0,0.5,0.0);
		cube();
	glPopMatrix();
	glPushMatrix();
		glScalef(1.0,1.0,1.0);
		glTranslatef(0.5,0.0,0.0);
		draw3Dcurve (1.0,1.0,2.0,270.0,360.0,5.0);
	glPopMatrix();
	glPushMatrix();
		glScalef(0.5,1.0,1.0);
		glTranslatef(0.5,-1.5,0.0);
		cube();
	glPopMatrix();
}
