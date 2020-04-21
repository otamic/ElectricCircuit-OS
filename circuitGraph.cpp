//
//  circuitGraph.cpp
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#include "circuitGraph.h"
#include <cstring>
#include <queue>

void ini_AMLGraph(AMLGraph & G, const Box box[], int map[10][10]) {
    G.vexNum = 0; G.edgeNum = 0;
    int nextdir[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (map[i][j] && box[map[i][j]].element == wire && wireIn(box[map[i][j]]) > 2) {
                G.adjmulist[G.vexNum].locX = j;
                G.adjmulist[G.vexNum].locY = i;
                G.vexNum++;
            }
        }
    
    for (int i = 0; i < G.vexNum; i++) {
        for (int j = 0; j < 4; j++)
            if (box[map[G.adjmulist[i].locY][G.adjmulist[i].locX]].in[j]) {
                G.edgs[G.edgeNum].ivex = i;
                addEgde(G, box, map, G.adjmulist[i].locX + nextdir[j][0], G.adjmulist[i].locY + nextdir[j][1], (j + 2) % 4);
            }
    }
    
    // ɾȥ���Ƶĵ�
    
    // ��ֱ�ӿ��Խ���ϵ������������
}

int wireIn(const Box & B) {                                                    // �ڵ��Ķ�
    int num = 0;
    for (int i = 0; i < 4; i++)
        if (B.in[i])
            num++;
    return num;
}

void addEgde(AMLGraph & G, const Box box[], int map[10][10], int vexX, int vexY, int dir) {
    int nextX = vexX, nextY = vexY, nextdir[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
    G.edgs[G.edgeNum].data.curVal = G.edgs[G.edgeNum].data.resVal = G.edgs[G.edgeNum].data.volVal = 0.0;
    while (wireIn(box[map[nextY][nextX]]) == 2) {
        switch (box[map[nextY][nextX]].element) {
            case resistance:
                G.edgs[G.edgeNum].data.resVal += box[map[nextY][nextX]].parameter;
                break;
            case curSource:
                if (dir == LEFT || dir == DOWN)
                    G.edgs[G.edgeNum].data.curVal += box[map[nextY][nextX]].parameter;
                else
                    G.edgs[G.edgeNum].data.curVal -= box[map[nextY][nextX]].parameter;
                break;
            case volSource:
                if (dir == LEFT || dir == DOWN)
                    G.edgs[G.edgeNum].data.volVal += box[map[nextY][nextX]].parameter;
                else
                    G.edgs[G.edgeNum].data.volVal -= box[map[nextY][nextX]].parameter;
                break;
        }
        for (int i = 0; i < 4; i++)
            if (box[map[nextY][nextX]].in[i] && i != dir) {
                dir = (i + 2) % 4;
                nextX += nextdir[i][0];
                nextY += nextdir[i][1];
                break;
            }
    }
    for (int i = 0; i < G.vexNum; i++)
        if (G.adjmulist[i].locX == nextX && G.adjmulist[i].locY == nextY) {
            G.edgs[G.edgeNum].jvex = i;
            break;
        }
    G.edgeNum++;
}

Vector getNodeVol(const AMLGraph & G) {
    using std::queue;
    queue<Edge> q;
    Matrix matri;
    Vector vec;
    ini_vector(vec, G.vexNum - 1);
    ini_matrix(matri, G.vexNum - 1, G.vexNum - 1);
    
    for (int i = 0; i < G.edgeNum; i++) {
        int spe = fillMatrix(G.edgs[i], matri, vec);
        if (spe) q.push(G.edgs[i]);
    }
    
    while (!q.empty()) {
        completeMatrix(q.front(), matri, vec, G.vexNum - 1);
        q.pop();
    }
    return crammer(matri, vec, G.vexNum - 1);
}

int fillMatrix(const Edge & E, Matrix & M, Vector & V) {            // ��iδҪ�����Ľڵ�
    if (E.ivex == 0) return 0;
    if (E.data.resVal && !E.data.curVal && !E.data.volVal) {        // ֻ�е���
        M[E.ivex - 1][E.ivex - 1] += 1 / E.data.resVal;
        if (E.jvex) M[E.ivex - 1][E.jvex - 1] -= 1 / E.data.resVal;
    }
    else if (E.data.volVal && !E.data.resVal && !E.data.curVal)        // ֻ�ж�����ѹԴ��Ҫ���⴦��
        return 1;
    else if (E.data.curVal && !E.data.resVal && !E.data.volVal)        // ֻ�ж�������Դ
        V[E.ivex - 1] -= E.data.curVal;
    else if (E.data.volVal && E.data.resVal && !E.data.curVal) {    // �а���ѹԴ
        M[E.ivex - 1][E.ivex - 1] += 1 / E.data.resVal;
        if (E.jvex) M[E.ivex - 1][E.jvex - 1] -= 1 / E.data.resVal;
        V[E.ivex - 1] -= E.data.volVal / E.data.resVal;
    }
    else                                                            // �а�����Դ
        V[E.ivex - 1] -= E.data.curVal;
    return 0;
}

void completeMatrix(const Edge & E, Matrix & M, Vector & V, int n) {
    if (E.jvex == 0) {
        for (int i = 0; i < n; i++)
            M[E.ivex - 1][i] = 0.0;
        M[E.ivex - 1][E.ivex - 1] = 1.0 / E.data.volVal;
        V[E.ivex - 1] = 0.0;
    }
    else {
        for (int i = 0; i < n; i++) {
            M[E.jvex - 1][i] += M[E.jvex - 1][i];
            M[E.jvex - 1][i] = 0.0;
        }
        M[E.jvex - 1][E.ivex - 1] = 1.0;
        M[E.jvex - 1][E.jvex - 1] = -1.0;
        V[E.jvex - 1] = -E.data.volVal;
    }
}


