//
//  circuitElem.cpp
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#include "circuitElem.h"
#include "drawElem.h"
//#include <GL/glut.h>

void ini_box(Box & B, elem e) {
    switch (e)
    {
        case resistance:
            B.element = resistance;
            B.in[LEFT] = B.in[RIGHT] = true;
            B.in[UP] = B.in[DOWN] = false;
            B.parameter = 1.0;
            break;
        case curSource:
            B.element = curSource;
            B.in[LEFT] = B.in[RIGHT] = true;
            B.in[UP] = B.in[DOWN] = false;
            B.parameter = 1.0;
            break;
        case volSource:
            B.element = volSource;
            B.in[LEFT] = B.in[RIGHT] = true;
            B.in[UP] = B.in[DOWN] = false;
            B.parameter = 1.0;
            break;
        case wire:
            B.element = wire;
            B.in[LEFT] = B.in[RIGHT] = true;
            B.in[UP] = B.in[DOWN] = false;
            B.parameter = 1.0;
            break;
        default:
            break;
    }
}

void paint_box(const Box & B, float x, float y) {
    switch (B.element) {
        case resistance:
            if (B.in[LEFT]) {
                glBegin(GL_LINE_LOOP);
                glVertex2f(x - 20.0, y - 10.0);
                glVertex2f(x + 20.0, y - 10.0);
                glVertex2f(x + 20.0, y + 10.0);
                glVertex2f(x - 20.0, y + 10.0);
                glEnd();
                glBegin(GL_LINES);
                glVertex2f(x - 40.0, y);
                glVertex2f(x - 20.0, y);
                glVertex2f(x + 20.0, y);
                glVertex2f(x + 40.0, y);
                glEnd();
            }
            else {
                glBegin(GL_LINE_LOOP);
                glVertex2f(x - 10.0, y - 20.0);
                glVertex2f(x + 10.0, y - 20.0);
                glVertex2f(x + 10.0, y + 20.0);
                glVertex2f(x - 10.0, y + 20.0);
                glEnd();
                glBegin(GL_LINES);
                glVertex2f(x, y - 40.0);
                glVertex2f(x, y - 20.0);
                glVertex2f(x, y + 20.0);
                glVertex2f(x, y + 40.0);
                glEnd();
            }
            break;
            
        case curSource:
            GLfloat plusx, plusy, minx, miny;
            if (B.in[LEFT]) {
                plusx = x + 30.0; plusy = y;
                minx = x + 20.0; miny = y;
                circleMidpoint(x, y, 15);
                glBegin(GL_LINES);
                glVertex2f(x - 40, y);
                glVertex2f(x - 15, y);
                glVertex2f(x + 15, y);
                glVertex2f(x + 40, y);
                glVertex2f(x, y - 15);
                glVertex2f(x, y + 15);
                glEnd();
            }
            else {
                plusx = x; plusy = y + 30.0;
                minx = x; miny = y + 20.0;
                circleMidpoint(x, y, 15);
                glBegin(GL_LINES);
                glVertex2f(x, y - 40);
                glVertex2f(x, y - 15);
                glVertex2f(x, y + 15);
                glVertex2f(x, y + 40);
                glVertex2f(x - 15, y);
                glVertex2f(x + 15, y);
                glEnd();
            }
            if (B.parameter > 0) {
                glBegin(GL_LINES);
                glVertex2f(plusx, plusy);
                if (B.in[LEFT]) {
                    glVertex2f(minx, miny + 10.0);
                    glVertex2f(plusx, plusy);
                    glVertex2f(minx, miny - 10.0);
                }
                else {
                    glVertex2f(minx + 10.0, miny);
                    glVertex2f(plusx, plusy);
                    glVertex2f(minx - 10.0, miny);
                }
                glEnd();
            }
            else {
                plusx = 2 * x - plusx; plusy = 2 * y - plusy;
                minx = 2 * x - minx; miny = 2 * y - miny;
                glBegin(GL_LINES);
                glVertex2f(plusx, plusy);
                if (B.in[LEFT]) {
                    glVertex2f(minx, miny + 10.0);
                    glVertex2f(plusx, plusy);
                    glVertex2f(minx, miny - 10.0);
                }
                else {
                    glVertex2f(minx + 10.0, miny);
                    glVertex2f(plusx, plusy);
                    glVertex2f(minx - 10.0, miny);
                }
                glEnd();
            }
            break;
            
        case volSource:
            if (B.in[LEFT]) {
                plusx = x - 15.0; plusy = y + 20.0;
                minx = x + 15.0; miny = y + 20.0;
                circleMidpoint(x, y, 15);
                glBegin(GL_LINES);
                glVertex2f(x - 40, y);
                glVertex2f(x + 40, y);
                glEnd();
            }
            else {
                plusx = x - 20.0; plusy = y - 15.0;
                minx = x - 20.0; miny = y + 15.0;
                circleMidpoint(x, y, 15);
                glBegin(GL_LINES);
                glVertex2f(x, y - 40);
                glVertex2f(x, y + 40);
                glEnd();
            }
            if (B.parameter > 0) {
                glRasterPos2f(plusx, plusy);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '+');
                glRasterPos2f(minx, miny);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '-');
            }
            else {
                glRasterPos2f(plusx, plusy);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '-');
                glRasterPos2f(minx, miny);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '+');
            }
            break;
            
        case wire:
            GLint inTime = 0;
            glBegin(GL_LINES);
            if (B.in[LEFT]) {
                glVertex2f(x, y);
                glVertex2f(x - 40.0, y);
                inTime++;
            }
            if (B.in[RIGHT]) {
                glVertex2f(x, y);
                glVertex2f(x + 40.0, y);
                inTime++;
            }
            if (B.in[UP]) {
                glVertex2f(x, y);
                glVertex2f(x, y + 40.0);
                inTime++;
            }
            if (B.in[DOWN]) {
                glVertex2f(x, y);
                glVertex2f(x, y - 40.0);
                inTime++;
            }
            glEnd();
            if (inTime > 2)
                circleMidpoint(x, y, 1);
            break;
    }
}

void changeDir_box(Box & B) {
    switch (B.element) {
        case resistance:
            B.in[LEFT] = !B.in[LEFT];
            B.in[RIGHT] = !B.in[RIGHT];
            B.in[UP] = !B.in[UP];
            B.in[DOWN] = !B.in[DOWN];
            break;
        case curSource:
        case volSource:
            if (B.parameter > 0)
                B.parameter = -B.parameter;
            else {
                B.in[LEFT] = !B.in[LEFT];
                B.in[RIGHT] = !B.in[RIGHT];
                B.in[UP] = !B.in[UP];
                B.in[DOWN] = !B.in[DOWN];
                B.parameter = -B.parameter;
            }
            break;
        case wire:
            
            break;
    }
}

float convert(GLubyte num[], int n) {
    float res = 0.0;
    int digit = 1;
    for (int i = n - 1; i >= 0; i--) {
        res += digit*(num[i] - '0');
        digit *= 10;
    }
    return res;
}
