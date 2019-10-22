/* ###################################################################
 **     Filename    : main.c
 **     Project     : Assignment2-Percy
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2019-10-14, 15:48, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "x.h"
#include "BitIoLdd1.h"
#include "y.h"
#include "BitIoLdd2.h"
#include "z.h"
#include "BitIoLdd3.h"
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "PWM1.h"
#include "PwmLdd1.h"
#include "TU3.h"
#include "Reset.h"
#include "BitIoLdd4.h"
#include "Sleep.h"
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
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <string.h>

int delay(int delay_time) {
	word time;
	FC321_Reset();
	do {
		FC321_GetTimeMS(&time);
	} while (time < delay_time);
}
void GUI_reset() {

}
int GUI(void) {
	Term1_Cls();
	Term1_MoveTo(5, 5);
	Term1_SendStr("today is Monday");
	Term1_SetColor(clYellow, clBlack);
	Term1_MoveTo(10, 1);
	Term1_SendStr("CC2511 Lab7");

}
extern volatile char c;
int x, y, z;

void box(int x_pos, int y_pos, int length, int hight, char colour_f,
		char colour_b) {
	Term1_SetColor(colour_f, colour_b);
	int x = x_pos;
	do {
		Term1_MoveTo(x, y_pos);
		Term1_SendChar(' ');
		Term1_MoveTo(x, y_pos + hight);
		Term1_SendChar(' ');
		x++;
	} while (x <= length);
	x = 0;
	do {
		Term1_MoveTo(x_pos, y_pos + 1);
		Term1_SendChar(' ');
		Term1_MoveTo(x_pos + length - 2, y_pos + 1);
		Term1_SendChar(' ');
		y_pos++;
	} while (y_pos <= hight);
}
void GUI_main() {
	// Display main GUI
	Term1_Cls();
	box(2, 2, 46, 4, clCyan, clCyan);
	Term1_MoveTo(12, 4);
	Term1_SetColor(clWhite, clBlack);
	Term1_SendStr("3 Axis milling GUI");
	//box(2,8,46,12,clMagenta,clMagenta);
	Term1_MoveTo(12, 9);
	Term1_SetColor(clWhite, clBlack);
	Term1_SendStr("Pleas make a selection");
	Term1_MoveTo(5, 12);
	Term1_SendStr("Use Keypad                >>> press (1)");
	Term1_MoveTo(5, 14);
	Term1_SendStr("Custom drawing            >>> press (2)");
	Term1_MoveTo(5, 16);
	Term1_SendStr("Set  X,Y,Z zero           >>> press (3)");
	Term1_MoveTo(5, 20);
	Term1_SendStr(">>>");
	Term1_MoveTo(2, 30);
	//Display current position
	Term1_SendStr("Current position");
	Term1_MoveTo(21, 30);
	Term1_SendNum(x);
	Term1_MoveTo(24, 30);
	Term1_SendNum(y);
	Term1_MoveTo(27, 30);
	Term1_SendNum(z);
	Term1_MoveTo(10, 20);

}

void GUI_manual() {
	//Display manual movement instructions
	//box(48, 8, 46, 11, clWhite, clBlack);
	Term1_MoveTo(50, 9);
	Term1_SendStr("Use the following key strokes to move the drill");
	Term1_MoveTo(50, 12);
	Term1_SendStr("W >>>>    + Y axis");
	Term1_MoveTo(50, 14);
	Term1_SendStr("S >>>>    - Y axis");
	Term1_MoveTo(50, 16);
	Term1_SendStr("D >>>>    + X axis");
	Term1_MoveTo(50, 18);
	Term1_SendStr("A >>>>    - X axis");
	Term1_MoveTo(50, 20);
	Term1_SendStr("U >>>>    + Z axis");
	Term1_MoveTo(50, 22);
	Term1_SendStr("J >>>>    - Z axis");
	Term1_MoveTo(50, 24);
	Term1_SendStr("+ >>>>    + Spindle Speed");
	Term1_MoveTo(50, 26);
	Term1_SendStr("- >>>>    - Spindle Speed");
	Term1_MoveTo(50, 28);
	Term1_SendStr("Q >>>>    Return to menu");
	Term1_MoveTo(10, 20);
}

void manual_movement() {
    int pwm_speed = 0;
	do {
		__asm ("wfi");
		// Move drill bit X Y Z
		if (c == 'w') {
			// move y +
			Dir_y_PutVal(1);
			y_NegVal();
			delay(50);
			y_NegVal();
			// New y position in relation to set zero point
			y++;
			Term1_MoveTo(24, 30);
			Term1_SendNum(y);
			c = 0;
		}
		else if (c == 's') {
			//move y -
			Dir_y_PutVal(0);
			y_NegVal();
			delay(50);
			y_NegVal();
			// New y position in relation to set zero point
			y--;
			Term1_MoveTo(24, 30);
			Term1_SendNum(y);
			c = 0;
		}
		else if (c == 'd') {
			//move x +
			Dir_x_PutVal(1);
			x_NegVal();
			delay(50);
			x_NegVal();
			// New x position in relation to set zero point
			x++;
			Term1_MoveTo(20, 30);
			Term1_SendNum(x);
			c = 0;
		}
		else if (c == 'a') {
			//move x -
			Dir_x_PutVal(0);
			x_NegVal();
			delay(50);
			x_NegVal();
			// New x position in relation to set zero point
			x--;
			Term1_MoveTo(20, 30);
			Term1_SendNum(x);
			c = 0;
		}
		else if (c == 'u') {
			//move z +
			Dir_z_PutVal(1);
			z_NegVal();
			delay(50);
			z_NegVal();
			// New x position in relation to set zero point
			z++;
			Term1_SendNum(z);
			Term1_MoveTo(28, 30);
			c = 0;
		}
		else if (c == 'j') {
			//move z -
			Dir_z_PutVal(0);
			z_NegVal();
			delay(50);
			z_NegVal();
			// New x position in relation to set zero point
			z--;
			Term1_SendNum(z);
			Term1_MoveTo(28, 30);
			c = 0;
		}
		//set PWM for drill bit speed
		else if(c == '+'){
				pwm_speed += 15;
				PWM1_SetRatio8(pwm_speed);
		}
		else if(c == '-'){
				pwm_speed -= 15;
				PWM1_SetRatio8(pwm_speed);
		}
	} while (c != 'q');
	c = 0;
	Term1_MoveTo(50, 9);
	Term1_EraseLine();
	Term1_MoveTo(50, 10);
	Term1_EraseLine();
	Term1_MoveTo(50, 12);
	Term1_EraseLine();
	Term1_MoveTo(50, 14);
	Term1_EraseLine();
	Term1_MoveTo(50, 16);
	Term1_EraseLine();
	Term1_MoveTo(50, 18);
	Term1_EraseLine();
	Term1_MoveTo(50, 20);
	Term1_EraseLine();
	Term1_MoveTo(50, 22);
	Term1_EraseLine();
	Term1_MoveTo(50, 24);
	Term1_EraseLine();
	Term1_MoveTo(50, 26);
	Term1_EraseLine();
	Term1_MoveTo(50, 28);
	Term1_EraseLine();
	Term1_MoveTo(10, 20);
	PWM1_SetRatio8(0);
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */

	GUI();
	Term1_SendStr("123today");
	GUI_main();

	for (;;) {

		__asm ("wfi");
		// Manual Control
		if (c == '1') {
			GUI_manual();
			manual_movement();
		}
		// set XYZ zero
		else if (c == '3') {
			Term1_MoveTo(50, 10);
			Term1_SendStr("to the zero position for all axis and press Q ");
			GUI_manual();
			manual_movement();
			z = 0;
			y = 0;
			x = 0;
		} else if (c == '2') {
			Term1_MoveTo(50, 9);
			Term1_SendStr("Not available ");
			c = 0;
		}
	}
	/* For example: for(;;) { } */

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
