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
#include "./kangaroo.h"



void drawKangaroo(int jump, float body_rot, float head_rot, float leg_rot, float foot_angle, float arm_rot, float tail_rot, float left_arm, float right_arm)
{
	glTranslatef(0, jump, 0); //move kangaroo up in y-axis
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
		glRotatef(right_arm, 1, 0, 0);
		drawArm();
	glPopMatrix();
	
	//attach tail
	glPushMatrix();
		glTranslatef(0,-7,-2);
		glRotatef(270.0,0,1,0);
		glRotatef(10.0,1,0,0); 
		glRotatef(tail_rot,0,0,1); //z-axis rotation affected by animation
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
		
		//attach snout
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
