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
#include "x_step.h"
#include "BitIoLdd1.h"
#include "z_step.h"
#include "BitIoLdd2.h"
#include "y_step.h"
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
#include "Dir_z.h"
#include "BitIoLdd7.h"
#include "Dir_y.h"
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
#include "Reset_y.h"
#include "BitIoLdd12.h"
#include "Sleep_y.h"
#include "BitIoLdd13.h"
#include "Reset_z.h"
#include "BitIoLdd14.h"
#include "Sleep_z.h"
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
#include "drawShapes.h"
extern volatile char c;



/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int x = 0;
	int y = 0;
	int z = 0;
	int p = 0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */


//	RGB('r');
	GUI_title(x,y,z,p);
	GUI_main();

	for (;;) {
//		__asm ("wfi");
		// Manual Control
		if (c == '1') {
			GUI_title(x,y,z,p);
			GUI_manual(x,y,z,p);
			manual_movement(x,y,z,p);

		}
		else if (c == '2') {
			GUI_title(x,y,z,p);
			Term1_MoveTo(5, 9);
//			Term1_SendStr("Not available now! Choose 1, 2 or 3");
			drawCircle(100);
			manual_movement(x,y,z,p);
			c = 0;

		}
		// set XYZ zero
		else if (c == '3') {
			z = 0;
			y = 0;
			x = 0;
			p = 0;
			GUI_title(x,y,z,p);
			Term1_MoveTo(5, 10);
			Term1_SendStr("To the zero position for all axis and press Q to return back");
			manual_movement(x,y,z,p);

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
