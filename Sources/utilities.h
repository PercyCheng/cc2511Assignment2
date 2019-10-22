/*
 * utilities.h
 *
 *  Created on: 22 Oct 2019
 *      Author: chengpeng
 */

#ifndef SOURCES_UTILITIES_H_
#define SOURCES_UTILITIES_H_


int delay(int delay_time) ;
void GUI_reset() ;
void RGB(char rgb);
void GUI_main();
void GUI_manual();
void manual_movement(int x,int y,int z,int p);
void box(int x_step_pos, int y_step_pos, int length, int hight, char colour_f,char colour_b) ;
void clean_promotion();
void promotion_reduce();
void promotion_add();

#endif /* SOURCES_UTILITIES_H_ */
