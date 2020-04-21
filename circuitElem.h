//
//  circuitElem.h
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#ifndef circuitElem_h
#define circuitElem_h

#include <GLUT/glut.h>

const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

typedef enum { resistance, curSource, volSource, wire, nul } elem;
typedef double ElemType;

/*
 typedef struct {
 bool up;
 bool down;
 bool left;
 bool right;
 } In;
 */

typedef struct {
    elem element;
    ElemType parameter;
    //    In in;
    bool in[4];
} Box;

void ini_box(Box & B, elem e);
void paint_box(const Box & B, float x, float y);
void changeDir_box(Box & B);
float convert(GLubyte num[], int n);

#endif /* circuitElem_h */
