/*
 * utilities.c
 *
 *  Created on: 22 Oct 2019
 *      Author: chengpeng
 */

#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "x_step.h"
#include "BitIoLdd1.h"
#include "y_step.h"
#include "BitIoLdd2.h"
#include "z_step.h"
#include "BitIoLdd3.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU3.h"
#include "Reset_x.h"
#include "BitIoLdd4.h"
#include "Sleep_x.h"
#include "BitIoLdd5.h"
#include "Dir_x.h"
#include "BitIoLdd6.h"
#include "Dir_y.h"
#include "BitIoLdd7.h"
#include "Dir_z.h"
#include "BitIoLdd8.h"
#include "Mode_1.h"
#include "BitIoLdd9.h"
#include "Mode_2.h"
#include "BitIoLdd10.h"
#include "Mode_3.h"
#include "BitIoLdd11.h"
#include "Red_LED.h"
#include "BitIoLdd15.h"
#include "Green_LED.h"
#include "BitIoLdd16.h"
#include "Blue_LED.h"
#include "BitIoLdd17.h"
#include "Reset_z.h"
#include "BitIoLdd12.h"
#include "Sleep_z.h"
#include "BitIoLdd13.h"
#include "Reset_y.h"
#include "BitIoLdd14.h"
#include "Sleep_y.h"
#include "BitIoLdd18.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
#include <string.h>

extern volatile char c;
// Delay function
int delay(int time_expect) {
	word time;
	FC321_Reset();
	do {
		FC321_GetTimeUS(&time);
	} while (time < time_expect);
}
//Drive x stepper motor
void driveMotorX(int delay_time, int x) {
	if (x < 0 || x > 1000) {
		LightRGB(7);
		Term1_MoveTo(60, 3);
		Term1_SetColor(clRed, clBlack);
		Term1_SendStr("Outside of work area!!");
		Term1_SetColor(clWhite, clBlack);
		for (int i = 0; i <= 20; i++) {
			x_step_NegVal();
			delay(delay_time);
			x_step_NegVal();
			delay(delay_time);
		}
	} else {
		LightRGB(1);
		Term1_MoveTo(60, 3);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			x_step_NegVal();
			delay(delay_time);
			x_step_NegVal();
			delay(delay_time);
		}

	}
}
//Drive y stepper motor
void driveMotorY(int delay_time, int y) {
	if (y < 0 || y > 500) {
		LightRGB(7);
		Term1_MoveTo(60, 4);
		Term1_SetColor(clRed, clBlack);
		Term1_SendStr("Outside of work area!!");
		Term1_SetColor(clWhite, clBlack);
		for (int i = 0; i <= 20; i++) {
			y_step_NegVal();
			delay(delay_time);
			y_step_NegVal();
			delay(delay_time);
		}
	} else {
		LightRGB(1);
		Term1_MoveTo(60, 4);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			y_step_NegVal();
			delay(delay_time);
			y_step_NegVal();
			delay(delay_time);
		}
	}
}
//Drive z stepper motor
void driveMotorZ(int delay_time, int z) {
	if (z < 0) {
		LightRGB(7);
		Term1_MoveTo(60, 5);
		Term1_SetColor(clRed, clBlack);
		Term1_SendStr("Outside of work area!!");
		Term1_SetColor(clWhite, clBlack);
		for (int i = 0; i <= 20; i++) {
			z_step_NegVal();
			delay(delay_time);
			z_step_NegVal();
			delay(delay_time);
		}
	} else {
		LightRGB(1);
		Term1_MoveTo(60, 5);
		Term1_EraseLine();
		for (int i = 0; i <= 20; i++) {
			z_step_NegVal();
			delay(delay_time);
			z_step_NegVal();
			delay(delay_time);
		}
	}
}
//this function will move spindle to the correct height to draw shapes
void fly_spindle(int mode, int depth,int z) {
	if (mode == 2) {
		for (int i = 0; i <= depth; i++) {
			Dir_z_PutVal(1);
			driveMotorZ(600,z);
		}
	} else if (mode == 1) {
		for (int i = 0; i <= depth; i++) {
			Dir_z_PutVal(0);
			driveMotorZ(600,z);
		}
	}
}
//Draw box in PuTTy
void box(int x_step_pos, int y_step_pos, int length, int hight, char colour_f,
		char colour_b) {
	Term1_SetColor(colour_f, colour_b);
	int x_step = x_step_pos;
	do {
		Term1_MoveTo(x_step, y_step_pos);
		Term1_SendChar(' ');
		Term1_MoveTo(x_step, y_step_pos + hight);
		Term1_SendChar(' ');
		x_step++;
	} while (x_step <= length);
	x_step = 0;
	do {
		Term1_MoveTo(x_step_pos, y_step_pos + 1);
		Term1_SendChar(' ');
		Term1_MoveTo(x_step_pos + length - 2, y_step_pos + 1);
		Term1_SendChar(' ');
		y_step_pos++;
	} while (y_step_pos <= hight);
}
//GUI for title box
void GUI_title(int x, int y, int z, int p) {
	//reset GUI
	Term1_Cls();
	// Display main GUI
	box(2, 2, 46, 5, clYellow, clYellow);
	Term1_MoveTo(15, 2);
	Term1_SetColor(clBlack, clYellow);
	Term1_SendStr("CC2511 A2 Group3 ");
	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(12, 4);
	Term1_SendStr("3 Axis milling GUI");
	Term1_MoveTo(12, 5);
	Term1_SendStr("Members:Kim, Kevin, Percy");

	//Display current position
	Term1_MoveTo(50, 2);
	Term1_SendStr("Current position:");
	Term1_MoveTo(50, 3);
	Term1_SendStr("X: ");
	Term1_MoveTo(55, 3);
	Term1_SendNum(x);
	Term1_MoveTo(50, 4);
	Term1_SendStr("Y: ");
	Term1_MoveTo(55, 4);
	Term1_SendNum(y);
	Term1_MoveTo(50, 5);
	Term1_SendStr("Z: ");
	Term1_MoveTo(55, 5);
	Term1_SendNum(z);

	//Display PWM
	Term1_MoveTo(50, 6);
	Term1_SendStr("PWM: ");
	Term1_MoveTo(55, 6);
	Term1_SendNum(p);
}

//Change RGB led
void LightRGB(int rgb) {
	if (rgb == 1) {
		Red_LED_SetVal();
		Blue_LED_SetVal();
		Green_LED_ClrVal();
	} else if (rgb == 2) {
		Blue_LED_ClrVal();
		Green_LED_SetVal();
		Red_LED_SetVal();
	} else if (rgb == 3) {
		Green_LED_SetVal();
		Red_LED_ClrVal();
		Blue_LED_ClrVal();
	} else if (rgb == 7) { // For error only RED
		Red_LED_ClrVal();
		Green_LED_SetVal();
		Blue_LED_SetVal();

	}
}

//GUI for main interface
void GUI_main() {
	Term1_MoveTo(5, 10);
	Term1_SetColor(clWhite, clBlack);
	Term1_SendStr("Please make a selection: ");
	Term1_MoveTo(5, 12);
	Term1_SendStr("Use Keypad                          >>> press (1)");
	Term1_MoveTo(5, 14);
	Term1_SendStr("Custom drawing                      >>> press (2)");
	Term1_MoveTo(5, 16);
	Term1_SendStr("Reset  X,Y,Z axis to zero           >>> press (3)");
	Term1_MoveTo(5, 20);
	Term1_SendStr(">>>");
}

//GUI for option 2
void GUI_manual() {
	//Display manual movement instructions
	Term1_MoveTo(5, 11);
	Term1_SendStr("Use the following key strokes to move the drill");
	Term1_MoveTo(5, 12);
	Term1_SendStr("W >>>>    + Y axis");
	Term1_MoveTo(5, 14);
	Term1_SendStr("S >>>>    - Y axis");
	Term1_MoveTo(5, 16);
	Term1_SendStr("D >>>>    + X axis");
	Term1_MoveTo(5, 18);
	Term1_SendStr("A >>>>    - X axis");
	Term1_MoveTo(5, 20);
	Term1_SendStr("I >>>>    + Z axis");
	Term1_MoveTo(5, 22);
	Term1_SendStr("J >>>>    - Z axis");
	Term1_MoveTo(5, 24);
	Term1_SendStr("< >>>>    + Spindle Speed");
	Term1_MoveTo(5, 26);
	Term1_SendStr("> >>>>    - Spindle Speed");
	Term1_MoveTo(5, 28);
	Term1_SendStr("Q >>>>    Return to menu");

}
//Clear GUI
void GUI_clear() {
	for (int i = 10; i <= 28; i++) {
		Term1_MoveTo(5, i);
		Term1_EraseLine();
	}
}
// Select shape to draw
void shape_operation(int d) {
	do {
		__asm ("wfi");
		if (c == 't') {
			//This function will draw triangle
			PWM1_SetRatio8(0);
			sendP(255);
			drawTriangle(100, d);
			c = '0';
			PWM1_SetRatio8(255);
			sendP(0);
		} else if (c == 'c') {
			//This function will draw circle
			PWM1_SetRatio8(0);
			sendP(255);
			drawCircle(200, d);
			c = '0';
			PWM1_SetRatio8(255);
			sendP(0);
		} else if (c == 'r') {
			//This function will draw circle
			PWM1_SetRatio8(0);
			sendP(255);
			drawRectangle(100, 50, d);
			c = '0';
			PWM1_SetRatio8(255);
			sendP(0);
		} else if (c == 'o') {
			//This function will draw circle
			PWM1_SetRatio8(0);

			sendP(255);
			draw_olympic(100, d);
			c = '0';
			PWM1_SetRatio8(255);
			sendP(0);
		}
	} while (c != 'q');
}
//Shapes GUI
void GUI_shapes() {
	//Display auto shapes
	Term1_MoveTo(5, 10);
	Term1_SendStr("Use the following key strokes to select shape");
	Term1_MoveTo(5, 12);
	Term1_SendStr("t >>>>    Triangle");
	Term1_MoveTo(5, 14);
	Term1_SendStr("r >>>>    Rectangle");
	Term1_MoveTo(5, 16);
	Term1_SendStr("c >>>>    Circle");
	Term1_MoveTo(5, 18);
	Term1_SendStr("O >>>>    Olmpic Rings");
	Term1_MoveTo(5, 20);
	Term1_SendStr("Q>>>>     Quit");
}

//The three functions below are control the prompt
//clean the promotion line
void clean_prompt() {
	Term1_MoveTo(50, 7);
	Term1_EraseLine();
	Term1_MoveTo(50, 8);
	Term1_EraseLine();
}

//promotion for requiring to deduct steps
void prompt_reduce() {
	Term1_MoveTo(50, 7);
	Term1_SendStr("PWM cannot go further");
	Term1_MoveTo(50, 8);
	Term1_SendStr("Please reduce PWM >>>> (,)!");
	Term1_SetColor(clWhite, clBlack);
	c = 0;
}

//promotion for requiring to add steps
void prompt_add() {
	Term1_MoveTo(50, 7);
	Term1_SendStr("PWM cannot go further");
	Term1_MoveTo(50, 8);
	Term1_SendStr("Please add PWM >>>> (.)!");
	Term1_SetColor(clWhite, clBlack);
	c = 0;
}

//Send X Y Z P
void sendX(int x) {
	Term1_MoveTo(55, 3);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 3);
	Term1_SendNum(x);
}
void sendY(int y) {
	Term1_MoveTo(55, 4);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 4);
	Term1_SendNum(y);
}
void sendZ(int z) {
	Term1_MoveTo(55, 5);
	Term1_SendStr("     ");
	Term1_MoveTo(55, 5);
	Term1_SendNum(z);
}
void sendP(int p) {
	Term1_MoveTo(55, 6);
	Term1_SendStr("    ");
	Term1_MoveTo(55, 6);
	Term1_SendNum(p);
}

//option 1 manual function
void manual_movement(int x, int y, int z, int p) {
	p = 255;
	sendP(p);
	PWM1_SetRatio8(p);
	sendP(255 - p);
	do {
		__asm ("wfi");
		// Move drill bit X Y Z
		if (c == 'd') {
			//move x_step +
			Dir_x_PutVal(1);
			driveMotorX(100,x);
			// New x_step position in relation to set zero point
			x++;
			sendX(x);
			c = 0;
		}

		else if (c == 'a') {
			//move x_step -
			Dir_x_PutVal(0);
			driveMotorX(100,x);
			// New x_step position in relation to set zero point
			x--;
			sendX(x);
			c = 0;

		} else if (c == 'w') {
			// move y_step +
			Dir_y_PutVal(1);
			driveMotorY(600,y);
			// New y_step position in relation to set zero point
			y++;
			sendY(y);
			c = 0;
		}

		else if (c == 's') {
			//move y_step -
			Dir_y_PutVal(0);
			driveMotorY(600,y);
			// New y_step position in relation to set zero point
			y--;
			sendY(y);
			c = 0;
		}

		else if (c == 'i') {
			//move z_step +
			Dir_z_PutVal(1);
			driveMotorZ(600,z);
			// New x_step position in relation to set zero point
			z++;
			sendZ(z);
			c = 0;
		} else if (c == 'j') {
			//move z_step -
			Dir_z_PutVal(0);
			driveMotorZ(600,z);
			// New x_step position in relation to set zero point
			z--;
			sendZ(z);
			c = 0;
		}
		//set PWM for drill bit speed
		else if (c == ',') {
			clean_prompt();
			if (p < 255) {
				p += 16;
				PWM1_SetRatio8(p);
				sendP(255 - p);
				c = 0;
			} else {
				prompt_add();

			}
		} else if (c == '.') {
			clean_prompt();
			if (p > 0) {
				p -= 16;
				PWM1_SetRatio8(p);
				sendP(255 - p);
				c = 0;
			} else {
				prompt_reduce();
			}
		}
	} while (c != 'q');

}
