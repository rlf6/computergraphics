#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "./R.h"
#include "./L.h"
#include "./F.h"
#include "./A.h"
#include "./J.h"
#include "./G.h"

#define NUMBER_OF_MODELS 13

//======================================================
// GLOBAL VARIABLES 
//======================================================
int current_model = 0;

float pitch = 0.0f;
float yaw = 0.0f;
float pitch0, yaw0;
bool MousePressed;
int mouseX0, mouseY0;
bool rotating=false;
//articulation
bool animated=false;
float foot_angle = 90;
float leg_rot = 30;
float body_rot = 45;
float arm_rot = 0;
int change = 1;

//
//Prototypes
void drawKangaroo();
void drawLeg();
void drawHead();
void drawBody();
void drawEar();
void drawArm();
void drawSnout();
void drawTail();



//======================================================
// DRAW AXES and GRIDS
//======================================================
void drawAxesAndGridLines(bool x_y_display, bool y_z_display,  bool x_z_display)
{
	float offset;
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(-20, 0, 0);					
		glVertex3f(+20, 0, 0);					
		glVertex3f( 0 ,-20, 0);				    	
		glVertex3f(	0, +20, 0);
		glVertex3f( 0, 0,-20);				    	
		glVertex3f(	0, 0, +20);

	glEnd();
	
	glLineStipple(1, 0xAAAA); //line style = fine dots
	glEnable(GL_LINE_STIPPLE);

	glBegin(GL_LINES);
		
		if (x_y_display) {glColor3f(0.0,0.7,0.7);
		for (offset=-10.0;offset<10.1;offset++){
			//draw lines in x-y plane
			glVertex3f(-10.0, offset, 0.0);					// Top Left
			glVertex3f(+10.0, offset, 0.0);					// Top Right
			glVertex3f( offset,-10, 0.0);					// Bottom Right
			glVertex3f(	offset,+10.0, 0.0);					// Bottom Left
		}}

		if (y_z_display) {glColor3f(0.7,0.0,0.7);
		for (offset=-10.0;offset<10.1;offset++){
			//draw lines in y-z plane
			glVertex3f( 0, offset, -10);					
			glVertex3f(	0, offset, 10.0);
			glVertex3f( 0, -10, offset);					
			glVertex3f(	0, 10, offset);
		}}

		if (x_z_display) {glColor3f(0.7,0.7,0.0);
		for (offset=-10.0;offset<10.1;offset++){
			//draw lines in x-z plane
			glVertex3f( offset, 0, -10);					
			glVertex3f(	offset, 0, 10.0);
			glVertex3f( -10, 0, offset);					
			glVertex3f(	10, 0, offset);
		}}

	glEnd();
	glDisable(GL_LINE_STIPPLE);

}

//======================================================
// VIEW CONTROL ROUTINES
//======================================================

void idleCallBack (){
	yaw=yaw+.25;
    glutPostRedisplay();
}

void rotateView(bool r){
	rotating = r;
	if (r) glutIdleFunc(idleCallBack); else glutIdleFunc(NULL);
}

void resetView(){
	rotateView(false); //Stop view rotation
	yaw=pitch=0;
}

void executeViewControl (float y, float p){
	glRotatef(y, 0.0f, 1.0f, 0.0f); //yaw about y-axis
    glRotatef(p, 1.0f, 0.0f, 0.0f); //pitch about x-axis 
}

void mouseClickCallBack(int button, int state, int x, int y) {
	//Called on button press or release
    switch (state)
    {
		case GLUT_DOWN:
			MousePressed = true;
			rotateView(false);
			pitch0 = pitch; yaw0 = yaw;
			mouseX0 = x; mouseY0 = y;
			break;
		default:
		case GLUT_UP:
			MousePressed = false;
			//rotateView(true);
			break;
    }
} 

void mouseMotionCallBack(int x, int y) 
{
	// Called when the Mouse is moved with left button down
    pitch = pitch0 + (y - mouseY0);
    yaw = yaw0 + (x - mouseX0);
	glutPostRedisplay();
} 

void reshapeCallBack(int w, int h) 
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	if (w == 0 || h == 0) return;
    if (w <= h) glOrtho(-3.0, 3.0, -3.0 * (GLfloat) h / (GLfloat) w, 3.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else        glOrtho(-3.0 * (GLfloat) w / (GLfloat) h, 3.0 * (GLfloat) w / (GLfloat) h, -3.0, 3.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void animate(int x)
{	
	body_rot += 3*change;
	leg_rot -= 10*change;
	foot_angle += 10*change;
	if(leg_rot == -30 || leg_rot == 30)
		{ change = change * -1; }
	glutPostRedisplay();
	glutTimerFunc(100, animate, x);
}
//======================================================
// KEYBOARD CALLBACK ROUTINE 
//======================================================
void keyboardCallBack(unsigned char key, int x, int y) {
	printf("Keyboard call back: key=%c, x=%d, y=%d\n", key, x, y);
	switch(key)
	{
	//model selection
	case 'm': case 'M':
		current_model++;
		if (current_model > NUMBER_OF_MODELS) current_model = 0;
	break;
	case 'b': case 'B':
		glPolygonMode(GL_BACK,GL_FILL);
	break;
	case 'f': case 'F':
		glPolygonMode(GL_FRONT,GL_FILL);
	break;
	case 'l': case 'L':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	break;
	case 'r': 
		rotating= !rotating;
		rotateView(rotating);
	break;
	case 'R':
        resetView();
	break;
	default:
		printf("Press b - back fill; f - front fill; l - line; i - increment; or d - decrement; r - rotate; R - reset view\n");
	}
	
	glutPostRedisplay();
}

void drawScene()
{
	drawAxesAndGridLines(true, true, true);
	
	glPushMatrix();
	
	switch(current_model)
	{
		case 0:
			drawKangaroo();
		break;
		case 1: 
			drawLeg();
		break;
		case 2:
			drawHead();
		break;
		case 3:
			drawBody();
		break;
		case 4:
			drawEar();
		break;
		case 5:
			drawSnout();
		break;
		case 6:
			drawArm();
		break;
		case 7:
			drawTail();
		break;
		case 8:
			drawJ();
		break;
		case 9:
			drawR();
		break;
		case 10:
			drawL();
		break;
		case 11:
			drawF();
		break;
		case 12:
			drawG();
		break;
		case 13:
			drawA();
		break;
		default:
			printf("Unknown model\n");
	}
	
	
	glPopMatrix();
}

void drawKangaroo()
{
	glScalef(0.7,0.7,0.7);
	glRotatef(body_rot, 1, 0, 0);
	drawBody();
	//attach head
	glPushMatrix();
		glTranslatef(0, 6.7, 0);
		glScalef(0.7, 0.7, 0.7);
		drawHead();
	glPopMatrix();
		
}
//draw body
void drawBody()
{
	//main part
	glPushMatrix();
		glTranslatef(0,3,0);
		glScalef(0.7,2,0.7);
		glPushMatrix();
			for(int i = 0; i < 360; i++)
			{
				glPushMatrix();
				glRotatef(i, 0, 1, 0);
				glTranslatef(-4, 0, 0);
				drawG();
				glPopMatrix();
			}           
		glPopMatrix();
	glPopMatrix();
	//attach legs
	glPushMatrix();
		glTranslatef(-2, -4.5, 0.5);
		drawLeg();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2, -4.5, 0.5);
		drawLeg();
	glPopMatrix();
	//attach arms
	glPushMatrix();
		glTranslatef(-2, -2, 0);
		glRotatef(arm_rot, 1, 0, 0);
		drawArm();
		glTranslatef(4, 0, 0);
		drawArm();
	glPopMatrix();
	//attach tail
	glPushMatrix();
		glTranslatef(0,-8,-6);
		glRotatef(270.0,0,1,0);
		glRotatef(10.0,1,0,0);
		glScalef(0.75,0.75,0.75);
		drawTail();
	glPopMatrix();
}

void drawTail()
{
		glPushMatrix();
			glTranslatef(1.0,0,0);
			glRotatef(90.0,0,0,1);
			glScalef(0.7,0.7,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.5,-0.5,0);
			glRotatef(100.0,0,0,1);
			glScalef(0.6,0.6,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-3.0,-2.5,0);
			glRotatef(130.0,0,0,1);
			glScalef(0.6,0.6,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-4.0,-4.3,0);
			glRotatef(145.0,0,0,1);
			glScalef(0.5,0.5,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-4.5,-5.6,0);
			glRotatef(160.0,0,0,1);
			glScalef(0.4,0.4,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-4.8,-6.9,0);
			glRotatef(170.0,0,0,1);
			glScalef(0.35,0.35,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-5.8,-8.2,0);
			glRotatef(150.0,0,0,1);
			glScalef(0.3,0.3,1.0);
			drawA();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-7.2,-9.2,0);
			glRotatef(130.0,0,0,1);
			glScalef(0.3,0.3,1.0);
			drawA();
		glPopMatrix();
}

void drawHead()
{
	//main part
	glPushMatrix();
		glTranslatef(0, 3, 0);
		glScalef(0.8, 1.5, 1);
		
		glPushMatrix();
			for(int i = 180; i < 360; i++)
			{
				glPushMatrix();
				glRotatef(i, 0, 1, 0);
				glTranslatef(-4, 0, 0);
				drawG();
				glPopMatrix();
			}         
		glPopMatrix();
		//snout
		glPushMatrix();
			glTranslatef(-2, -3, 0);
			drawSnout();
		glPopMatrix();
		//attach ears
		glPushMatrix();
			glRotatef(-25, 1, 0, 0);
			glPushMatrix();
				glTranslatef(-2, 1, -0.5);
				drawEar();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2, 1, -0.5);
				drawEar();
			glPopMatrix();
		glPopMatrix();
		//eyes
		glPushMatrix();
			glScalef(0.5, 0.35, 0.8);
			glPushMatrix();
				glTranslatef(-6, -2, 0.6);
				drawA();
			glPopMatrix();
			glPushMatrix();	
				glTranslatef(2, -2, 0.6);
				drawA();
			glPopMatrix();
		glPopMatrix();
		
	glPopMatrix();
}

void drawEar()
{
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glPushMatrix();
			glTranslatef(-2, 5 , 0);
			glScalef(1, 1.5, 1);
			drawA();
		glPopMatrix();
	glPopMatrix();
}

void drawArm()
{
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
		glPushMatrix();
			glScalef(1.5,1.0,1.0);
			glRotatef(90.0,0,0,1);
			drawJ();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.8,-3.0,0.0);
			glRotatef(120.0,0,0,1);
			glScalef(0.75,1.0,1.0);
			drawF();
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void drawSnout()
{
	glPushMatrix();
		glTranslatef(2, -0.5, 5);
		glRotatef(100, 1, 0, 0); glRotatef(-90, 0, 1, 0);
		glScalef(0.4, 1, 1);
		drawR();
		glPushMatrix();
			glRotatef(20, 1, 0, 0);
			drawR();
			glRotatef(-40, 1, 0, 0);
			drawR();
		glPopMatrix();
		glPushMatrix();
			glRotatef(30, 0, 0, 1);
			drawR();
		glPopMatrix();
	glPopMatrix();
}

void drawLeg()
{
	//upper leg
	glRotatef(leg_rot, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-45, 0, 0, 1);
	glPushMatrix();
		glTranslatef(3, 0, 0);
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			drawF();
		glPopMatrix();
		glTranslatef(-0.5, -4, 0);
		drawL();
		//foot
		glPushMatrix();
			glTranslatef(2, -5.5, 0);
			glRotatef(foot_angle, 0, 0, 1);
			drawL();
		glPopMatrix();
	glPopMatrix();
}
		
		
//======================================================
// DISPLAY CALL BACK ROUTINE 
//======================================================
void displayCallBack()	
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	executeViewControl (yaw, pitch);
	
	
	glScalef(0.2, 0.2, 0.2);
	drawAxesAndGridLines(true, true, true);

    drawScene();
				 
	glutSwapBuffers();
	
}

//======================================================
// MAIN PROGRAM
//======================================================
int main(int argc, char** argv)
{
   // Allow cmd line arguments to be passed to the glut
	glutInit(&argc, argv);

	// Create and name window
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Need both double buffering and z buffer
    glutInitWindowSize(500, 500);
    glutCreateWindow("Computer Graphics Project - Kangaroo");

	// Add Display & Mouse CallBacks
	glutReshapeFunc(reshapeCallBack);
	glutDisplayFunc(displayCallBack);
	glutIdleFunc(NULL); // Starts the Idle Function as having no routine attached to it. This is modified in rotateView()
	glutMouseFunc(mouseClickCallBack);
    glutMotionFunc(mouseMotionCallBack);
	glutKeyboardFunc(keyboardCallBack);
	
	int x; 
	animate(x);
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

	// Print Application Usage
	printf("Program Controls:\n");
	printf("Left Mouse Button & Drag - Changes the View.\n");
	printf("Key \"1\" - Animate\n");
	printf("Key \"b\" - Back Fill.\n");
	printf("Key \"f\" - Front Fill.\n");
	printf("Key \"l\" - Wire Frame/Line Fill.\n");
	printf("Key \"r\" - Automated Rotation.\n");
	printf("Key \"R\" - Reset the View.\n");

	glutMainLoop();

	return 0;
}
