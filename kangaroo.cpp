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
bool animated= false;
bool dancing = false;
float foot_angle = 90;
float leg_rot = 0;
float body_rot = 0;
float arm_rot = 0;
float tail_rot = 0;
float head_rot = 0;
float left_arm = 0;
float right_arm = 0;

int jump = 1;
int change = 1;
int arm_change = 1;
//
//Prototypes
void drawKangaroo(int jump, float body_rot, float head_rot, float leg_rot, float foot_angle, float arm_rot, float tail_rot, float left_arm, float right_arm);
void drawLeg(float leg_rot, float foot_angle);
void drawHead();
void drawBody(float left_arm, float right_arm, float tail_rot, float leg_rot, float foot_angle);
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

void idleCallBack()
{
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


void jumping(int x)
{	
	body_rot += 3*change;
	leg_rot -= 13*change;
	foot_angle += 14*change;
	tail_rot -= 6*change;
	jump += 1*change*-1;
	if(leg_rot < -30 || leg_rot > 20)
		{ change = change * -1; }
	glutPostRedisplay();
	if(animated)
	{ 
		glutTimerFunc(100, jumping, x); 
	}
}

void dance(int x)
{	
	left_arm += 3*arm_change;
	right_arm -= 3*arm_change;
	head_rot += 3*arm_change;
	tail_rot += 5*arm_change;
	if(left_arm == -30 || left_arm == 30 )
		{ arm_change = arm_change * -1; }
	glutPostRedisplay();
	if(dancing)
	{
		glutTimerFunc(40, dance, x);
	}
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
	case 'a': case 'A':
	//turn on/off animation
		if(animated)
		{
			animated = false;
			foot_angle = 110;
			leg_rot = 10;
			body_rot = 0;
			arm_rot = 0;
			tail_rot = 0;
			change = 1;
			jump = 1;
		}
		else if(!animated)
		{	
			body_rot = 35;
			foot_angle = 90;
			animated = true;
			jumping(1);
		}
	break;
	case 's' : case 'S':
		if(dancing)
		{
			dancing = false;
			left_arm = 0;
			right_arm = 0;
			head_rot = 0;
			tail_rot = 0;
		}
		else if(!dancing)
		{
			dancing = true;
			dance(1);
		}
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
	
	//model viewer
	switch(current_model)
	{
		case 0:
			drawKangaroo(jump, body_rot, head_rot, leg_rot, foot_angle, arm_rot, tail_rot, left_arm, right_arm);
		break;
		case 1: 
			drawLeg(leg_rot, foot_angle);
		break;
		case 2:
			drawHead();
		break;
		case 3:
			drawBody(left_arm, right_arm, tail_rot, leg_rot, foot_angle);
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

void drawKangaroo(int jump, float body_rot, float head_rot, float leg_rot, float foot_angle, float arm_rot, float tail_rot, float left_arm, float right_arm)
{
	glTranslatef(0, jump, 0);
	glPushMatrix();
		glScalef(0.7,0.7,0.7);
		glRotatef(body_rot, 1, 0, 0);
		drawBody(left_arm, right_arm, tail_rot, leg_rot, foot_angle);
		//attach head
		glPushMatrix();
			glTranslatef(0, 3, 0);
			glRotatef(head_rot, 1, 0, 0);
			glScalef(0.7, 0.7, 0.7);
			drawHead();
		glPopMatrix();
	glPopMatrix();
		
}
//draw body
void drawBody(float left_arm, float right_arm, float tail_rot, float leg_rot, float foot_angle)
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
		drawLeg(leg_rot, foot_angle);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2, -4.5, 0.5);
		drawLeg(leg_rot, foot_angle);
	glPopMatrix();
	//attach arms
	glPushMatrix();
		glTranslatef(-2, -2, 0);
		glRotatef(left_arm, 1, 0, 0);
		drawArm();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2, -2, 0);
		glRotatef(right_arm,1,0,0);
		drawArm();
	glPopMatrix();
	//attach tail
	glPushMatrix();
		glTranslatef(0,-7,-2);
		glRotatef(270.0,0,1,0);
		glRotatef(10.0,1,0,0);
		glRotatef(tail_rot,0,0,1);
		glScalef(0.75,0.75,0.75);
		drawTail();
	glPopMatrix();
}

void drawTail()
{
	glTranslatef(-5, 0, 0);
	glPushMatrix();
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
	glPopMatrix();
}

void drawHead()
{
	//main part
	glTranslatef(0, 5, 0);
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

void drawLeg(float leg_rot, float foot_angle)
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
	
	
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

	// Print Application Usage
	printf("Program Controls:\n\n");
	printf("Key \"a or A\" - Watch the kangaroo jump!\n");
	printf("Key \"s or S\" - See the kangaroo dance!\n\n");
	printf("Left Mouse Button & Drag - Changes the View.\n");
	printf("Key \"b\" - Back Fill.\n");
	printf("Key \"f\" - Front Fill.\n");
	printf("Key \"l\" - Wire Frame/Line Fill.\n");
	printf("Key \"r\" - Automated Rotation.\n");
	printf("Key \"R\" - Reset the View.\n");

	glutMainLoop();

	return 0;
}
