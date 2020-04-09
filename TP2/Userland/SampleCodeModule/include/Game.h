#ifndef GAME_H
#define GAME_H

#include "gamePrinter.h"
#define R_BLOCKS  4                                   //Cantidad de filas de bloques
#define C_BLOCKS  5                                   //Cantidad de columnas de bloques

typedef enum ballDirec{LU, U, RU, RD, D, LD} ballDirec;                                                         //Left up, up, right up, right down, down, left down
typedef enum walls{NONE = 0, LEFT, RIGHT, UPPER, FLOOR, URCORNER, ULCORNER, LRCORNER, LLCORNER } walls;           //los bordes de la pantalla
typedef enum barSides{N = 0, L, R, UL, UM, UR} barSides;                                                             //none, left, right, upperLeft, UpperMiddle, UpperRight

struct Ball {
    int pos[2];                                    //pelota en el medio de ls pantalla
    int vel;                                       //la velocidad cuenta de a cuantos cuadraditos se mueve
    ballDirec dir;
};
struct Blocks{
    int matrix[R_BLOCKS][C_BLOCKS];                     //matriz de los bloques
    int left; 
};
struct Time{
    int past;                   //tiempo en el juego time_past
    int tick;
};



//devuelve 0 si no fue precionada la tecla especial
int stopKeyPressed();

void print_ball(int* ball_pos,int color);

void print_bar(int* bar_pos,int color);

int left_arrow_pressed();

int right_arrow_pressed();

void print_block(int x, int y,int color);

//Inicialiizar el juego desde cero
int runGame(void);


//para volver si fue pausado
int startGame(void);
void startGameRec(void);


void print_blocks();


void handleBallMov();

//void handleBarMov();
/*Le cambia la direccion a la pelota dependiendo exactamente donde cae en la barra
    Si cae en la parte de arriba la barra se divide en tres:
        A la izquierda: va a salir 135 grados(LU)
        En el medio a 90 grados(arriba, U)
        A la derecha a 45gados(RU)
    si cae en uno de los lados:
        derecha: sale a -45 grados(RD)
        izquierda: sale a 225 grados(RD)
*/
void ballHitBarChangeDireccion(barSides side);

//Le cambia la posicion a la pelota dependiendo su pos y direccion y vel
void ballMove();

barSides ballHitBar();

//hace que la pelotita cambie de direccion si choca con una pared o bloque
void invertDirection(walls wall);

//devuelve que pared le esta pegando y false(osea 0) si no le pega a ninguna
walls ballHitWall();

//devuelve la pared que esta tocando y false(osea 0) si no esta tocando
walls barHitWall();

//Devuelve en block la pos en la mariz del bloque que choco y que borde del bloque, sino choco devuelve NO_BLOCK en la primer pos
void ballHitBlock();

//para ver si la la pelota(auxPos), esta dentro del rectangulo marcado
int insideSquare(int * auxPos, int * LLSquare, int * URSquare);

void makeSquare(int * square, int x, int y);

//devuelve que borde del bloque esta chocando la pelota, se devuelve la pared que representa ese borde(ya que actua de la misma forma)
walls ballTouchingWall(int c, int r);

//Se fija si la pelota esta o no en el rango y del bloque correspondiente a {c,r} (column , row)
int ballBetweenYSides(int * auxPos, int c, int r);

//Se fija si la pelota esta o no en el rango x del bloque correspondiente a {c,r} (column , row)
int ballBetweenXSides(int * auxPos, int c, int r);

int ballBetween(int auxPos, int y1, int y2);

int finishGame(int time_past);

void ballNextPos(int * auxPos);

#endif