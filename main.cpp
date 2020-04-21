//
//  main.cpp
//  circuit
//
//  Created by 冯彦澄 on 2019/1/1.
//  Copyright © 2019 冯彦澄. All rights reserved.
//

#include <GLUT/glut.h>
#include "circuitGraph.h"

#include <cstdio>

GLsizei WIDTH = 1200, HEIGHT = 800;                                // ���ڲ���
GLfloat squreHalW = 40;                                            // Ԫ�����������εİ��߳�

const int BOX_MAX = 105;
GLint map[10][10] = { 0 };                                        // ��·����ͼ
Box box[BOX_MAX], midBox;                                        // Ԫ�����飬δ����Ԫ��
GLint boxNum;                                                    // ����Ԫ������
GLint adress[BOX_MAX][2];                                        // Ԫ������ӳ�䵽��·������
GLfloat midBoxX, midBoxY;                                        // δ����Ԫ���ľ���λ��
GLfloat cenResistanceX = 100.0, cenResistanceY = 700.0;            // ����ͼ���ľ���λ��
GLfloat cenCurSorX = 100.0, cenCurSorY = 500.0;                    // ��������Դͼ���ľ���λ��
GLfloat cenVolSorX = 100.0, cenVolSorY = 300.0;                    // ������ѹԪͼ���ľ���λ��
GLfloat cenWireX = 100.0, cenWireY = 100.0;                        // ����ͼ���ľ���λ��

GLint showX, showY;                                                // Ҫ��ʾ/�޸Ĳ�����Ԫ��������λ��
GLboolean isShow = false;                                        // ����Ҫ��ʾ������Ԫ��
GLubyte input[100];                                                // �������ݴ���λ��
GLint inputNum = 0;                                                // �������ݵĳ���
GLboolean set;                                                    // �Ƿ�����������Ӧ

AMLGraph G;
Vector res;
GLboolean isShowRes = false;
GLint resX = 1000, resY = 400;


void init(void);
void Display(void);
void Reshape(GLsizei newWidth, GLsizei newHeight);
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void myKeyboard(unsigned char key, int x, int y);

elem inCenSquare(GLfloat x, GLfloat y);                            // �ж���������ʱ����λ��
void drawBoxes();                                                // ��������Ԫ��
void updateWire(Box & B, GLint x, GLint y);                        // ���µ��ߵĶ�
void showInfor(GLint x, GLint y);                                // ��ʾԪ���Ĳ���
void showInput();                                                // ��ʾ����������

void getRes();
void showRes();
void showFloat(GLfloat num);

int main(int argc, char ** argv)
{
    
    
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("A mouse function");
    
    init();
    glutDisplayFunc(Display);
    glutMouseFunc(myMouse);
    glutMotionFunc(myMotion);
    glutKeyboardFunc(myKeyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
    return 0;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);                        // ������ɫΪ��ɫ
    
    // ��ʼ���ĸ��̶�Ԫ��
    ini_box(box[0], resistance);
    ini_box(box[1], curSource);
    ini_box(box[2], volSource);
    ini_box(box[3], wire);
    adress[0][0] = midBoxX = cenResistanceX; adress[0][1] = midBoxY = cenResistanceY;
    adress[1][0] = cenCurSorX; adress[1][1] = cenCurSorY;
    adress[2][0] = cenVolSorX; adress[2][1] = cenVolSorY;
    adress[3][0] = cenWireX; adress[3][1] = cenWireY;
    boxNum = 4;
    
    ini_box(midBox, resistance);
}


void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // ����
    glColor3f(1, 0, 0);                                // ��ɫ
    glBegin(GL_LINES);
    for (int i = 40; i <= 760; i += 80) {
        glVertex2i(200 + 40, i);
        glVertex2i(200 + 760, i);
    }
    for (int i = 40; i <= 760; i += 80) {
        glVertex2i(200 + i, 40);
        glVertex2i(200 + i, 760);
    }
    glEnd();
    
    glColor3f(1, 1, 1);                                // ��ɫ
    drawBoxes();                                    // ����Ԫ��
    
    if (isShow)                                        // ����Ҫ��ʾ������Ԫ��
        showInfor(showX, showY);
    
    if (isShowRes)
        showRes();
    
    showInput();                                    // ��������
    
    glutSwapBuffers();
}

void Reshape(GLsizei newWidth, GLsizei newHeight) {    // ������Ҫ�ı䴰�ڴ�С
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, newWidth, newHeight);
    gluOrtho2D(0, newWidth, 0, newHeight);
    WIDTH = newWidth;
    HEIGHT = newHeight;
    glMatrixMode(GL_MODELVIEW);
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {                // ��������
        elem ele = inCenSquare(x, y);
        if (ele != nul) {                                                // �ڼ���ͼ��λ�ã�������Ӧ
            ini_box(midBox, ele);
            set = true;
        }
        else if (x >= 200 && x <= 1000 && y >= 0 && y <= 800) {            // ��������
            GLint nx = (x - 200) / 80, ny = (HEIGHT - y) / 80;
            if (map[ny][nx] && box[map[ny][nx]].element != wire) {        // ��Ԫ��
                isShow = true;
                showX = nx;
                showY = ny;
            }
            else
                isShow = false;
            glutPostRedisplay();
        }
        else {
            isShow = false;                                                // �ر���ʾ����
            glutPostRedisplay();
        }
    }
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && set) {        // ����̧���������ڰ������������Ԫ��
        
        int nx = (x - 200) / 80, ny = (HEIGHT - y) / 80;
        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && !map[ny][nx]) {
            map[ny][nx] = boxNum;
            adress[boxNum][0] = nx; adress[boxNum][1] = ny;
            ini_box(box[boxNum], midBox.element);
            ini_box(midBox, resistance);
            midBoxX = cenResistanceX; midBoxY = cenResistanceY;
            boxNum++;
            set = false;
            glutPostRedisplay();
        }
    }
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {                // �Ҽ�̧��������Ԫ���ı�Ԫ������
        int nx = (x - 200) / 80, ny = (HEIGHT - y) / 80;
        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && map[ny][nx]) {
            changeDir_box(box[map[ny][nx]]);
            glutPostRedisplay();
        }
    }
}

void myMotion(int x, int y) {
    if (set) {                                                            // �������ڰ����������δ����Ԫ��λ��
        midBoxX = x;
        midBoxY = HEIGHT - y;
        glutPostRedisplay();
    }
}

void myKeyboard(unsigned char key, int x, int y) {                        // ��������
    if (key >= '0' && key <= '9')
        input[inputNum++] = key;
    else if (key == ' ') {                                                // ���²���
        if (isShow) {
            if (box[map[showY][showX]].parameter > 0)
                box[map[showY][showX]].parameter = convert(input, inputNum);
            else
                box[map[showY][showX]].parameter = -convert(input, inputNum);
        }
        inputNum = 0;
    }
    else if (key == 'c' || key == 'C') {                                // ��ͼ�����ɽڵ���ѹ
        getRes();
    }
    glutPostRedisplay();
}

elem inCenSquare(GLfloat x, GLfloat y) {                                // ��������λ��
    if (x >= cenResistanceX - squreHalW && x <= cenResistanceX + squreHalW && y >= HEIGHT - cenResistanceY - squreHalW && y <= HEIGHT - cenResistanceY + squreHalW)
        return resistance;
    if (x >= cenCurSorX - squreHalW && x <= cenCurSorX + squreHalW && y >= HEIGHT - cenCurSorY - squreHalW && y <= HEIGHT - cenCurSorY + squreHalW)
        return curSource;
    if (x >= cenVolSorX - squreHalW && x <= cenVolSorX + squreHalW && y >= HEIGHT - cenVolSorY - squreHalW && y <= HEIGHT - cenVolSorY + squreHalW)
        return volSource;
    if (x >= cenWireX - squreHalW && x <= cenWireX + squreHalW && y >= HEIGHT - cenWireY - squreHalW && y <= HEIGHT - cenWireY + squreHalW)
        return wire;
    return nul;
}

void drawBoxes() {                                                        // ����Ԫ��
    for (int i = 0; i < 4; i++)
        paint_box(box[i], adress[i][0], adress[i][1]);
    for (int i = 4; i < boxNum; i++) {
        if (box[i].element == wire && i != 3)
            updateWire(box[i], adress[i][0], adress[i][1]);
        paint_box(box[i], 240 + adress[i][0] * 80, 40 + adress[i][1] * 80);
    }
    paint_box(midBox, midBoxX, midBoxY);
}

void updateWire(Box & B, GLint x, GLint y) {                            // ���µ��ߵĶ�
    GLint xx, yy;
    xx = x; yy = y + 1;
    if (xx >= 0 && xx < 10 && yy >= 0 && yy < 10 && map[yy][xx] && (box[map[yy][xx]].in[DOWN] || box[map[yy][xx]].element == wire))
        B.in[UP] = true;
    else
        B.in[UP] = false;
    xx = x; yy = y - 1;
    if (xx >= 0 && xx < 10 && yy >= 0 && yy < 10 && map[yy][xx] && (box[map[yy][xx]].in[UP] || box[map[yy][xx]].element == wire))
        B.in[DOWN] = true;
    else
        B.in[DOWN] = false;
    xx = x + 1; yy = y;
    if (xx >= 0 && xx < 10 && yy >= 0 && yy < 10 && map[yy][xx] && (box[map[yy][xx]].in[LEFT] || box[map[yy][xx]].element == wire))
        B.in[RIGHT] = true;
    else
        B.in[RIGHT] = false;
    xx = x - 1; yy = y;
    if (xx >= 0 && xx < 10 && yy >= 0 && yy < 10 && map[yy][xx] && (box[map[yy][xx]].in[RIGHT] || box[map[yy][xx]].element == wire))
        B.in[LEFT] = true;
    else
        B.in[LEFT] = false;
}

void showInfor(GLint x, GLint y) {                                        // ��ʾԪ������
    glRasterPos2i(1000, 700);
    char * p = "Parameter = ";
    for (int i = 0; i < 12; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, p[i]);
    int a = int(box[map[y][x]].parameter);
    if (a < 0) a = -a;
    char num[100]; int i = 0;
    while (a) {
        num[i++] = '0' + a % 10;
        a /= 10;
    }
    for (int j = i - 1; j >= 0; j--)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, num[j]);
}

void showInput() {                                                        // ��ʾ��������
    glRasterPos2i(1000, 600);
    char * p = "Input = ";
    for (int i = 0; i < 8; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, p[i]);
    for (int i = 0; i < inputNum; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, input[i]);
}

void getRes() {
    ini_AMLGraph(G, box, map);
    res = getNodeVol(G);
    isShowRes = true;
    /*
     printf("%d ", G.vexNum);
     for (int i = 0; i < G.vexNum - 1; i++)
     printf("%lf ", res[i]);
     */
}

void showRes() {
    GLint xx = G.adjmulist[0].locX, yy = G.adjmulist[0].locY;
    glRasterPos2f(240 + xx * 80 + 10, 40 + yy * 80 + 10);
    showFloat(0);
    for (int i = 1; i < G.vexNum; i++) {
        xx = G.adjmulist[i].locX;
        yy = G.adjmulist[i].locY;
        glRasterPos2f(240 + xx * 80 + 10, 40 + yy * 80 + 10);
        showFloat(res[i - 1]);
    }
}

void showFloat(GLfloat num) {
    char digit[100];
    int len = 0;
    if (num < 0) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '-');
        num = -num;
    }
    int integer = (int)num;
    num -= integer;
    do {
        digit[len++] = '0' + integer % 10;
        integer /= 10;
    } while (integer);
    for (int i = len - 1; i >= 0; i--)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, digit[i]);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '.');
    for (int i = 0; i < 6; i++) {
        num *= 10;
        integer = (int)num;
        num -= integer;
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0' + integer);
    }
}
