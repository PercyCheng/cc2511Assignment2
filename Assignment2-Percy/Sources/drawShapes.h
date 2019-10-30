/*
 * drawShapes.h
 *
 *  Created on: 22 Oct 2019
 *      Author: chengpeng
 */

#ifndef SOURCES_DRAWSHAPES_H_
#define SOURCES_DRAWSHAPES_H_

void resetSpindle(int x, int y);
void centerSpindle(int x, int y, int boardLength);
void drawRectangle(int length, int height);
void moveSpindleTo(int x, int y, int x_before, int y_before);
void drawProgressBarUP(int x, int barLength, int radius);
void drawProgressBarSW(int x, int barLength, int radius);
void drawCircle(int x, int y, int radius);
void drawTriangle(int x, int y, int base);
void draw_Olympic(int radius);


#endif /* SOURCES_DRAWSHAPES_H_ */
