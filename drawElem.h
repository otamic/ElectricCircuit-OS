//
//  drawElem.h
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#ifndef drawElem_h
#define drawElem_h

#include <GLUT/glut.h>

void setPixel(GLint xCoord, GLint yCoord);
void circlePlotPoints(GLint, GLint, GLint, GLint);
void circleMidpoint(GLint xc, GLint yc, GLint radius);

#endif /* drawElem_h */
