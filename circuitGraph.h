//
//  circuitGraph.h
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#ifndef circuitGraph_h
#define circuitGraph_h

#include "circuitElem.h"
#include "matrix.h"

const int MAXNUM = 105;

typedef struct {
    float resVal;
    float curVal;
    float volVal;
} EdgeVal;

typedef struct Edge{
    int ivex, jvex;
    EdgeVal data;
} Edge;

typedef struct{
    int locX, locY;
} Vex;

typedef struct {
    Vex adjmulist[MAXNUM];
    Edge edgs[MAXNUM];
    int vexNum, edgeNum;
} AMLGraph;

void ini_AMLGraph(AMLGraph & G, const Box box[], int map[10][10]);
int wireIn(const Box & B);
void addEgde(AMLGraph & G, const Box box[], int map[10][10], int vexX, int vexY, int dir);
Vector getNodeVol(const AMLGraph & G);
int fillMatrix(const Edge & E, Matrix & M, Vector & V);
void completeMatrix(const Edge & E, Matrix & M, Vector & V, int n);


#endif /* circuitGraph_h */
