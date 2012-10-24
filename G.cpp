#include <stdlib.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./3Dcurve.h"
#include "./cube.h"

void drawG()
{
	glPushMatrix();
		glTranslatef(2.0,-2.0,0.0);
		glScalef(1.0,1.0,1.0);
		draw3Dcurve (1.0,1.0,2.0,0.0,180.0,5.0);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.5,-2.75,0.0);
		glScalef(1.0,1.5,1.0);
		cube();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(2.0,-3.5,0.0);
		glScalef(1.0,1.0,1.0);
		draw3Dcurve(1.0,1.0,2.0,180.0,360.0,5.0);
	glPopMatrix();
	
	glPushMatrix();
		glScalef(2.0,1.0,1.0);
		glTranslatef(1.5,-3.0,0.0);
		cube();
	glPopMatrix();
	
}

