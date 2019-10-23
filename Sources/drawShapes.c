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






extern volatile char c;
int i;


//reset spindle
void resetSpindle(int x, int y){

	for(i = 2; i < x; i--){
		Dir_x_PutVal(0);
		x_step_NegVal();
		x_step_NegVal();
	}
	//move y to middle
	for(i = 2; i < y; i--){
		Dir_x_PutVal(0);
		y_step_NegVal();
		y_step_NegVal();
	}
}

//move spindle to center
void centerSpindle(int x, int y, int boardLength){
	//this function will lead center point to middle of the milling board
	//center x
	if (x < boardLength){
		for(i = 0; i < boardLength - x; i++ ){
			Dir_x_PutVal(1);
			x_step_NegVal();
			x_step_NegVal();
		}
	}else{
		for(i = 0; i < x - boardLength; i++ ){
			Dir_x_PutVal(1);
			x_step_NegVal();
			x_step_NegVal();
		}
	}

	//TO DO: center y
};

//reset spindle before use this function
//To do: draw rectangle
void drawRectangle(int length, int height){
	//put spindle down


	//draw one length
	for(i = 0; i < length; i++){
		Dir_x_PutVal(1);
		x_step_NegVal();
		x_step_NegVal();
	}
	//draw one height
	for(i = 0; i < height; i++){
		Dir_y_PutVal(1);
		y_step_NegVal();
		y_step_NegVal();
	}
	//draw other length
	for(i=0; i < length; i++){
		Dir_x_PutVal(0);
		x_step_NegVal();
		x_step_NegVal();
	}
	//draw other height
	for(i = 0; i < height; i++){
		Dir_y_PutVal(0);
		y_step_NegVal();
		y_step_NegVal();
	}

}

//monitor coordinate
void moveSpindleTo(int x, int y, int x_before, int y_before){
	//update x position
	//eg. dot (15,5) move to (17,5)
	if (x > x_before){
		for (i = 0; i <= x - x_before; i++){
			Dir_x_PutVal(1);
			x_step_NegVal();
			x_step_NegVal();
		}
	//eg. dot (17,5) move to (15,5)
	}else if(x < x_before){
		Dir_x_PutVal(0);
		x_step_NegVal();
		x_step_NegVal();
	}else if(x = x_before){

	}

	////update y position
	//eg. dot (9,5) move to (9,7)
	if (y > y_before){
		for (i = 0; i <= y - y_before; i++){
			Dir_y_PutVal(1);
			y_step_NegVal();
			y_step_NegVal();
		}
	//eg. dot (9,7) move to (9,5)
	}else if(y < y_before){
		Dir_y_PutVal(0);
		y_step_NegVal();
		y_step_NegVal();
	}else if(y = y_before){
	}

}


//center spindle before use this function
void drawCircle(int radius){
	int x, y, r2;
	int x_before, y_before;
	//move spindle on circle(-radius, 0)
	for (i = 0; i <= radius; i++){
		Dir_y_PutVal(0);
		y_step_NegVal();
		y_step_NegVal();
	}

	r2 = radius * radius;

	for (x = -radius; x <=  radius; x++) {
		x_before = -radius - 1;
		//use math library
		y = sqrt(r2 - x*x);
		moveSpindleTo(x, y, x_before, y_before);
		x_before = x;
		y_before = y;
	}
}





