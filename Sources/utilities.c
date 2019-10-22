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
int delay(int delay_time) {
	word time;
	FC321_Reset();
	do {
		FC321_GetTimeMS(&time);
	} while (time < delay_time);
}
void GUI_reset() {

}
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
void GUI_title(int x, int y, int z, int p){
	//reset GUI
	Term1_Cls();
	// Display main GUI
	box(2, 2, 46, 5, clYellow, clYellow);
	Term1_MoveTo(12, 2);
	Term1_SetColor(clBlack, clYellow);
	Term1_SendStr("CC2511 A2 Group3 ");
	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(12, 4);
	Term1_SendStr("3 Axis milling GUI");
	Term1_MoveTo(12, 5);
	Term1_SendStr("Members:Kim, Kevin, Percy");

	//Display current position

	Term1_MoveTo(50,2);
	Term1_SendStr("Current position");
	Term1_MoveTo(50,3);
	Term1_SendStr("X: ");
	Term1_MoveTo(55,3);
	Term1_SendNum(x);
	Term1_MoveTo(50,4);
	Term1_SendStr("Y: ");
	Term1_MoveTo(55,4);
	Term1_SendNum(y);
	Term1_MoveTo(50,5);
	Term1_SendStr("Z: ");
	Term1_MoveTo(55,5);
	Term1_SendNum(z);
	//Display PWM
	Term1_MoveTo(50,6);
	Term1_SendStr("PWM: ");
	Term1_MoveTo(55,6);
	Term1_SendNum(p);
}


void RGB(char rgb){
	Blue_LED_NegVal();

}


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

void GUI_manual() {
	//Display manual movement instructions
	//box(48, 8, 46, 11, clWhite, clBlack);
	Term1_MoveTo(5, 10);
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

//void clean_promotion(){
//	Term1_MoveTo(50,8);
//	Term1_EraseLine();
//	Term1_MoveTo(50,9);
//	Term1_EraseLine();
//}
//
//void promotion_reduce(){
//	Term1_MoveTo(50,7);
//	Term1_SetColor(clRed,clBlack);
//	Term1_SendStr("Step cannot go further");
//	Term1_MoveTo(50,8);
//	Term1_SendStr("Please reduce step");
//	Term1_SetColor(clWhite,clBlack);
//	c = 0;
//}
//void promotion_add(){
//	Term1_MoveTo(50,7);
//	Term1_SetColor(clRed,clBlack);
//	Term1_SendStr("Step cannot go further");
//	Term1_MoveTo(50,8);
//	Term1_SendStr("Please reduce step");
//	Term1_SetColor(clWhite,clBlack);
//	c=0;
//}

void manual_movement(int x,int y,int z,int p) {

	do {
		__asm ("wfi");
		// Move drill bit X Y Z
		if (c == 'd') {
			//clean promotion lines
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();
			//correct minor steps
			if(x<255){
				//move x_step +
				Dir_x_PutVal(1);
				x_step_NegVal();
				//delay(50);
				x_step_NegVal();
				// New x_step position in relation to set zero point
				x++;
				Term1_MoveTo(55,3);
				Term1_SendStr("  ");
				Term1_MoveTo(55,3);
				Term1_SendNum(x);
				c = 0;
			}else{
				x=255;
				Term1_MoveTo(50,7);
				Term1_SetColor(clRed,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please reduce step!");
				Term1_SetColor(clWhite,clBlack);
				c = 0;
			}

		}
		else if (c == 'a') {
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();

			if (x>0){
				//move x_step -
				Dir_x_PutVal(0);
				x_step_NegVal();
				//delay(50);
				x_step_NegVal();
				// New x_step position in relation to set zero point
				x--;
				Term1_MoveTo(55,3);
				Term1_SendStr("  ");
				Term1_MoveTo(55, 3);
				Term1_SendNum(x);
				c = 0;
			}else{
				x=0;
				Term1_MoveTo(50,7);
				Term1_SetColor(clRed,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please add step!");
				Term1_SetColor(clWhite,clBlack);
				c = 0;

			}

		}
		else if (c == 'w') {
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();

			if (y<255){
				// move y_step +
				Dir_y_PutVal(1);
				y_step_NegVal();
				//delay(50);
				y_step_NegVal();
				// New y_step position in relation to set zero point
				y++;
				Term1_MoveTo(55,4);
				Term1_SendStr("  ");
				Term1_MoveTo(55,4);
				Term1_SendNum(y);
				c = 0;
			}else{
				y=255;
				Term1_MoveTo(50,7);
				Term1_SetColor(clBlue,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please reduce steps!");
				Term1_SetColor(clWhite,clBlack);
				c = 0;
			}
		}
		else if (c == 's') {
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();

			if(y>0){
				//move y_step -
				Dir_y_PutVal(0);
				y_step_NegVal();
				//delay(50);
				y_step_NegVal();
				// New y_step position in relation to set zero point
				y--;
				Term1_MoveTo(55,4);
				Term1_SendStr("  ");
				Term1_MoveTo(55,4);
				Term1_SendNum(y);
				c = 0;
			}else{
				y=0;
				Term1_MoveTo(50,7);
				Term1_SetColor(clBlue,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please add steps!");
				Term1_SetColor(clWhite,clBlack);
				c=0;

			}
		}

		else if (c == 'i') {
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();

			if (z<255){
				//move z_step +
				Dir_z_PutVal(1);
				z_step_NegVal();
				//delay(50);
				z_step_NegVal();
				// New x_step position in relation to set zero point
				z++;
				Term1_MoveTo(55,5);
				Term1_SendStr("  ");
				Term1_MoveTo(55, 5);
				Term1_SendNum(z);
				c = 0;
			}else{
				z=255;
				Term1_MoveTo(50,7);
				Term1_SetColor(clMagenta,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please reduce steps!");
				Term1_SetColor(clWhite,clBlack);
				c = 0;
			}
		}
		else if (c == 'j') {
			Term1_MoveTo(50,7);
			Term1_EraseLine();
			Term1_MoveTo(50,8);
			Term1_EraseLine();

			if(z > 0){
				//move z_step -
				Dir_z_PutVal(0);
				z_step_NegVal();
				//delay(50);
				z_step_NegVal();
				// New x_step position in relation to set zero point
				z--;
				Term1_MoveTo(55,5);
				Term1_SendStr("  ");
				Term1_MoveTo(55,5);
				Term1_SendNum(z);
				c = 0;
			}else{
				z = 0;
				Term1_MoveTo(50,7);
				Term1_SetColor(clMagenta,clBlack);
				Term1_SendStr("Step cannot go further");
				Term1_MoveTo(50,8);
				Term1_SendStr("Please add step!");
				Term1_SetColor(clWhite,clBlack);
				c=0;
			}
		}
		//set PWM for drill bit speed
		else if(c == '.'){
			Term1_MoveTo(50,7);
				Term1_EraseLine();
				Term1_MoveTo(50,8);
				Term1_EraseLine();

			if (p < 255){
				p += 15;
				PWM1_SetRatio8(p);
				Term1_MoveTo(55,6);
				Term1_SendStr("    ");
				Term1_MoveTo(55,6);
				Term1_SendNum(p);
				c = 0;
			}
			else{
				p=0;

			}
		}
		else if(c == ','){
			Term1_MoveTo(50,8);
				Term1_EraseLine();
				Term1_MoveTo(50,9);
				Term1_EraseLine();

			if (p > 0){
				p -= 15;
				PWM1_SetRatio8(p);
				Term1_MoveTo(55,6);
				Term1_SendStr("    ");
				Term1_MoveTo(55,6);
				Term1_SendNum(p);
				c = 0;
			}
			else{
				p=255;

			}
		}
	} while (c != 'q');
	GUI_title(x,y,z,p);
	GUI_main(x,y,z,p);

}