/*
 * utilities.h
 *
 *  Created on: 22 Oct 2019
 *      Author: chengpeng
 */

#ifndef SOURCES_UTILITIES_H_
#define SOURCES_UTILITIES_H_


int delay(int delay_time) ;
void driveMotorX(int delay_time);
void driveMotorY(int delay_time);
void driveMotorZ(int delay_time);
void fly_spindle(int mode,int depth);
void GUI_reset() ;
void GUI_main();
void GUI_manual();
void manual_movement(int x,int y,int z,int p);
void sendX(int x);
void sendY(int y);
void sendZ(int z);
void sendP(int p);
void box(int x_step_pos, int y_step_pos, int length, int hight, char colour_f,char colour_b) ;
void clean_promotion();
void promotion_reduce();
void promotion_add();
void shape_operation();
void GUI_shapes();
void GUI_clear();
void LightRGB(int rgb);
void GUI_title(int x, int y, int z, int p);
#endif /* SOURCES_UTILITIES_H_ */
