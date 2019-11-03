/*
 * drawShapes.c
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
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <string.h>
#include "utilities.h"
#include <stdio.h>
#include <math.h>

//reset spindle before use this function
extern volatile char c;

void drawTriangle(int base, int depth) {

	GUI_clear();
	fly_spindle(1, 30);
	Term1_MoveTo(10, 13);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("Triangle is being drawn! Progress Bar Is Shown Below: ");
	for (int i = 0; i <= base; i++) {
		Dir_x_PutVal(1);
		driveMotorX(1);
		Term1_SetColor(clWhite, clBlack);
		sendX(i);
		//draw 33% progress bar
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(20 + 5 * (i / 3 / base), 15); //5 is barLength
		Term1_SendStr("   ");
		Term1_SendNum(100 * i / 3 / base);
		Term1_SendStr(" %");
	}
	for (int i = 0; i <= base; i++) {
		Dir_y_PutVal(1);
		driveMotorY(1);
		Term1_SetColor(clWhite, clBlack);
		sendY(i);
		//draw 33% progress bar
		Term1_SetColor(clCyan, clRed);
		Term1_MoveTo(20 + 5 * (1 + i / 3 / base), 15); //5 is barLength
		Term1_SendStr("   ");
		Term1_SendNum(100 / 3 + 100 * i / 3 / base);
		Term1_SendStr(" %");
	}
	Dir_y_NegVal();
	Dir_x_NegVal();
	for (int i = 0; i <= base; i++) {
		driveMotorX(1);
		driveMotorY(1);
		//draw 33% progress bar
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(20 + 5 * (2 + i / 3 / base), 15); //5 is barLength
		Term1_SendStr("   ");
		Term1_SendNum(1 + 2 * 100 / 3 + 100 * i / 3 / base);
		Term1_SendStr(" %");
		Term1_SetColor(clWhite, clBlack);
		sendY(base - i);
		sendX(base - i);
	}
	Term1_SetColor(clYellow, clBlack);
	Term1_MoveTo(10, 17);
	Term1_SendStr("Well Done! Circle has been drawn!");
	Term1_MoveTo(10, 19);
	Term1_SendStr("Press Q to Return");
	fly_spindle(2, 30);

}

void drawRectangle(int length, int height, int depth) {

	//put spindle down
	int i;
	//draw one length
	GUI_clear();
	fly_spindle(1, 30);
	Term1_MoveTo(10, 13);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("Rectangle is being drawn! Progress Bar Is Shown Below: ");

	for (i = 0; i < length; i++) {
		Dir_x_PutVal(1);
		driveMotorX(1);
		//draw 25% progress bar
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(15 + 5 * (i / 4 / length), 15); //5 is barLength
		Term1_SendStr("   ");
		Term1_SendNum(1 + 100 * i / 4 / length);
		Term1_SendStr(" %");
		Term1_SetColor(clWhite, clBlack);
		sendX(i);

	}
	//draw one height
	for (i = 0; i < height; i++) {
		Dir_y_PutVal(1);
		driveMotorY(1);
		//draw 50% progress bar
		Term1_SetColor(clCyan, clRed);
		Term1_MoveTo(15 + 5 * (1 + i / 4 / height), 15);
		Term1_SendStr("   ");
		Term1_SendNum(26 + 100 * i / 4 / height);
		Term1_SendStr(" %");
		Term1_SetColor(clWhite, clBlack);
		sendY(i);

	}
	//draw other length
	for (i = 0; i < length; i++) {
		Dir_x_PutVal(0);
		driveMotorX(1);
		//draw 75% progress bar
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(15 + 5 * (2 + i / 4 / length), 15); //5 is barLength
		Term1_SendStr("   ");
		Term1_SendNum(51 + 100 * i / 4 / length);
		Term1_SendStr(" %");
		Term1_SetColor(clWhite, clBlack);
		sendX(height - i);
	}
	//draw other height
	for (i = 0; i < height; i++) {
		Dir_y_PutVal(0);
		driveMotorY(1);
		//draw 100% progress bar
		Term1_SetColor(clCyan, clRed);
		Term1_MoveTo(15 + 5 * (3 + i / 4 / height), 15);
		Term1_SendStr("   ");
		Term1_SendNum(76 + 100 * i / 4 / height);
		Term1_SendStr(" %");
		Term1_SetColor(clWhite, clBlack);
		sendY(length - i);
	}
	Term1_SetColor(clYellow, clBlack);
	Term1_MoveTo(10, 17);
	Term1_SendStr("Well Done! Circle has been drawn!");
	Term1_MoveTo(10, 19);
	Term1_SendStr("Press Q to Return");
	fly_spindle(2, 30);
}

//monitor coordinate
void moveSpindleTo(int x, int y, int x_before, int y_before, int delay_time) {
	int i;
	int n = 10;
	if (x > x_before) {
		for (i = 0; i <= x - x_before; i++) {
			for (int m = 0; m < n; m++) {
				Dir_x_PutVal(1);
				x_step_NegVal();
				delay(delay_time);
				x_step_NegVal();
				delay(delay_time);
			}
		}

	} else if (x < x_before) {
		for (i = 0; i <= x_before - x; i++) {
			for (int m = 0; m < n; m++) {
				Dir_x_PutVal(0);
				x_step_NegVal();
				delay(delay_time);
				x_step_NegVal();
				delay(delay_time);
			}
		}
	}

	if (y > y_before) {
		for (i = 0; i <= y - y_before; i++) {
			for (int m = 0; m < n; m++) {
				Dir_y_PutVal(1);
				y_step_NegVal();
				delay(delay_time);
				y_step_NegVal();
				delay(delay_time);
			}
		}

	} else if (y < y_before) {
		for (i = 0; i <= y_before - y; i++) {
			for (int m = 0; m < n; m++) {
				Dir_y_PutVal(0);
				y_step_NegVal();
				delay(delay_time);
				y_step_NegVal();
				delay(delay_time);
			}
		}
	}
}

//draw bar
void drawProgressBarUP(int x, int barLength, int radius) {
	//draw progress bar
	Term1_SetColor(clCyan, clYellow);
	Term1_MoveTo(25 + barLength * (x / 4 / radius), 15);
	Term1_SendStr("   ");
	Term1_SendNum(100 * x / 4 / radius);
	Term1_SendStr(" %");
	if (x <= 0) {
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(10 + barLength * ((radius + x) / 4 / radius), 15);
		Term1_SendStr("   ");
		Term1_SendNum(100 * (radius + x) / 4 / radius);
		Term1_SendStr(" %");
	} else {
		Term1_SetColor(clCyan, clRed);
		Term1_MoveTo(10 + barLength * (1 + x / 4 / radius), 15);
		Term1_SendStr("   ");
		Term1_SendNum(25 + 100 * x / 4 / radius);
		Term1_SendStr(" %");
	}
}
void drawProgressBarDW(int x, int barLength, int radius) {
	//draw progress bar
	Term1_SetColor(clMagenta, clGreen);
	Term1_MoveTo(25 + barLength * (1 + x / 4 / radius), 15);
	Term1_SendStr("   ");
	Term1_SendNum(101 - 100 * x / 4 / radius);
	Term1_SendStr(" %");
	if (x >= 0) {
		Term1_SetColor(clCyan, clMagenta);
		Term1_MoveTo(10 + barLength * (2 + -x / 4 / radius), 15);
		Term1_SendStr("  ");
		Term1_SendNum(50 + 100 * (radius - x) / 4 / radius);
		Term1_SendStr(" %");
	} else {
		Term1_SetColor(clCyan, clRed);
		Term1_MoveTo(10 + barLength * (3 + (radius - x) / 4 / radius), 15);
		Term1_SendStr("   ");
		Term1_SendNum(75 + 100 * (radius - x) / 4 / radius);
		Term1_SendStr("% ");
	}
}
//center spindle before use this function
void drawCircle(int radius, int depth) {
	int x;
	int y;
	GUI_clear();
	//move spindle down to sheet
	fly_spindle(1, 30);
	//initialize parameter
	int r2;
	int x_before = 0, y_before = 0;
	r2 = radius * radius;
	Term1_MoveTo(10, 13);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("Circle is being drawn! Progress Bar Is Shown Below: ");
	//draw semicircle

	for (x = 0; x <= radius * 2; x++) {
		//use math library
		y = 1.15 * 1.15 * sqrt(r2 - ((x - radius) * (x - radius)));
		moveSpindleTo(x, y, x_before, y_before, 1);
		x_before = x;
		y_before = y;
		Term1_SetColor(clWhite, clBlack);
		sendX(x);
		sendY(y);
		drawProgressBarUP(x, 5, radius);
	}

	for (x = radius * 2; x >= 0; x--) {
		y = -1.15 * 1.15 * sqrt(r2 - ((x - radius) * (x - radius)));
		moveSpindleTo(x, y, x_before, y_before, 1);
		x_before = x;
		y_before = y;
		Term1_SetColor(clWhite, clBlack);
		sendX(x);
		sendY(y);
		drawProgressBarDW(x, 5, radius);
	}

	Term1_SetColor(clYellow, clBlack);
	Term1_MoveTo(10, 17);
	Term1_SendStr("Well Done! Circle has been drawn!");
	Term1_MoveTo(10, 19);
	Term1_SendStr("Press Q to Return");
	//move spindle up
	fly_spindle(2, 30);
}

//draw olmpic
void draw_olympic(int radius, int depth) {
	PWM1_SetRatio8(0);
	int x;
	drawCircle(radius, 30);
	Dir_x_PutVal(1);
	for (x = radius * 2; x >= 0; x--) {
		driveMotorX(1);
	}
	drawCircle(radius, 30);
	Dir_x_PutVal(1);
	for (x = radius * 2; x >= 0; x--) {
		driveMotorX(1);
	}
	drawCircle(radius, 30);
	Dir_x_PutVal(0);
	for (x = radius * 3; x >= 0; x--) {
		driveMotorX(1);
	}
	Dir_y_PutVal(0);
	for (x = radius; x >= 0; x--) {
		driveMotorY(1);
	}
	drawCircle(radius, 30);
	Dir_x_PutVal(1);
	for (x = 2 * radius; x >= 0; x--) {
		driveMotorX(1);
	}
	drawCircle(radius, 30);
	PWM1_SetRatio8(255);
	sendP('0');
}

