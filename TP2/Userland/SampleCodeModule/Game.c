#include "./include/Game.h"
#include "../Include/Time.h"
#include "../Include/Curses.h"
#include "../Include/Time.h"
#include "../Include/deviceInfo.h"
#include <stdbool.h>
#include "./include/Speaker.h"

#define LIVESi                      3//cantidad de vidas al iniciar el juego    

#define BAR_LENGTH                  (17*SCREEN_WIDTH/100)
#define BAR_HEIGHT                  (4*SCREEN_HEIGHT/200)                
#define BAR_YPOS                    (78*SCREEN_HEIGHT/100)

#define BLOCK_WIDTH                 ((2*SCREEN_WIDTH/3) / C_BLOCKS)
#define BLOCK_XSEPARATION           ((SCREEN_WIDTH/3) / C_BLOCKS)
#define BLOCK_HEIGHT                ( (SCREEN_HEIGHT/2) / ( R_BLOCKS + 2) )
#define BLOCK_YSEPARATION           ( (2*BLOCK_HEIGHT ) / (R_BLOCKS +2 ))

#define BALL_RADIO                  (SCREEN_HEIGHT/100) 

#define bar_vel                     (2*SCREEN_WIDTH/100)

#define REAL_TO_GAME_TICKS              (1)
#define BALL_INITIAL_VELOCITY (3)



//COLORES
    #define BLACK                       0x000000
    #define WHITE                       0xFFFFFF
    #define BLUE                        0x0000FF
    #define GREEN                       0x00FF00
    #define AQUA                        0x00FFFF
    #define RED                         0xFF0000
    #define PURPLE                      0XBB00FF
    #define YELLOW                      0xFFFF00
    #define LightBlue                   0x6677FF
    #define LightGreen                  0x33FF44
    #define LightRed                    0xFF00FF
    #define LightPurple                 0x7700FF
  
//

#define X                           0
#define Y                           1

#define NO_BLOCK                   -1

#define LEFT_ARROW                 'j'
#define RIGHT_ARROW                'l' 
#define LEAVE_KEY                  'q'


static int lives = -1;                    //cantidad de vidas que tiene

static struct Ball ball={{-1,-1},-1,-1};

static int bar_pos[2] = {-1,-1};

static struct Blocks blocks = {-1,-1};

static struct Time time={-1,-1};

int block[3]={-1,-1,-1};

static char KeyBuffer[200];
static int keyBufferFront = 0;
static int keyBufferBack = 0;

static bool goToTerminal = false;

static int SCREEN_HEIGHT= -1;
static int SCREEN_WIDTH= -1;
static int info[2]={-1,-1};

static uint64_t gameTicks = -1;

static int initialize= -1;
//DECLARACION DE FUNCIONES
    void printObjects(int * curr_BallPos, int * curr_BarPos,int * block);
    void printLeftover(int * curr_BarPos);
    int key_pressed();
    void parseKeyboard();
    bool limitInput(char ch);
    void table();
    void tableData();
    void changeVel();
    void manageSound(uint64_t realTick);
//

static bool startOver = true;


//para inicializar el juego de cero
int runGame(void){
    if(initialize==1){
        startGame();
        return 0;
    }
    initialize=1;
    int aux;
    getScreenWidth(&aux);
    SCREEN_WIDTH=aux;
    getScreenHeight(&aux);
    SCREEN_HEIGHT=aux;    
    time.past=0;
    time.tick = 0;
    lives = LIVESi;
    blocks.left= R_BLOCKS*C_BLOCKS;       
        gameTicks = 0;
                     
    
    ball.pos[X]=SCREEN_WIDTH/2;
    ball.pos[Y]=SCREEN_HEIGHT/2;      
    ball.vel= BALL_INITIAL_VELOCITY;
    ball.dir = D; 
    
    bar_pos[X]=SCREEN_WIDTH/2;
    bar_pos[Y]=BAR_YPOS; 
    
    info[X]=SCREEN_WIDTH/2;
    info[Y]=SCREEN_HEIGHT-(SCREEN_HEIGHT-BAR_YPOS)/2;
    //pongo la matriz de bloques todos en uno, (osea que estan)
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            blocks.matrix[j][i]= 1;
        }
    }

    /*comienza el juego  */
    startGame();      
    
    return 0;
}





//cuando quiero retomar el juego
int startGame(){
    int aux;
    print_blocks();
    table();

    bool stopWhile = false;
    goToTerminal = false;
	uint64_t baseTicks = 0,realTicks = 0, previusTick = 0;

    baseTicks = getTicks();
    do{
        realTicks = getTicks() - baseTicks;
        parseKeyboard();

        if(realTicks % REAL_TO_GAME_TICKS == 0 && realTicks != previusTick){
            gameTicks++;
            previusTick = realTicks;
            if((aux = stopKeyPressed()) || lives==0 || blocks.left == 0 ){
                // Condicion de retorno
                stopWhile = true;
            }else
            {
                startGameRec();
            }

            manageSound(gameTicks);

        }


    }while(!stopWhile);

    stopSound();

    if(aux){ 
        startOver = false;
        return 0;
    }
        
    if(lives == 0  || blocks.left == 0 ){
        int x=finishGame(time.tick / 18);
        initialize=0;
        if(x==0)
            goToTerminal=true;
        else
        {   
            runGame();
        }        
    } 
    return 0;
}



//juega recursivamente
void startGameRec(void){
    tableData(); 
    time.tick ++;
    int curr_BallPos[]={ball.pos[X], ball.pos[Y]};
    int curr_BarPos[]={bar_pos[X], bar_pos[Y]};
    
    /*MOVIMIENTO DE LA BARRA*/
    handleBarMov();
    
    /*MOVIMIENTO DE LA PELOTA*/
    handleBallMov();

    changeVel();

    printObjects(curr_BallPos, curr_BarPos, block);
}
void changeVel(){
    if(time.tick % (15 *18) == 0){
        ball.vel+=1;
    }
}

void printObjects(int * curr_BallPos, int * curr_BarPos,int * block){
    printLeftover(curr_BarPos);
    print_ball(curr_BallPos,BLACK ); 
    print_ball(ball.pos, PURPLE );
    int x, y;
    if(block[X]!= NO_BLOCK){
        x = block[0];
        y = block[1];
        matrixToXY(&x, &y);
        print_block(x, y, BLACK);   
    }
    print_bar(bar_pos, BLUE);
    
}

void matrixToXY(int * c, int * r){
    *c = (*c * BLOCK_WIDTH) + (BLOCK_WIDTH/2)+ BLOCK_XSEPARATION*(*c+1) ;
    *r = (*r * BLOCK_HEIGHT) + (BLOCK_HEIGHT/2) + BLOCK_YSEPARATION*(*r+1) ;        
}
void printLeftover(int * curr_BarPos){
    int auxPos[]= {0,0};
    int length = bar_pos[X] - curr_BarPos[X];
    if(length > 0){// yendo para la derecha
        auxPos[X] = bar_pos[X] - BAR_LENGTH - length/2;
        auxPos[Y] =  bar_pos[Y];
        printOnScreen(auxPos, BAR_LENGTH, BAR_HEIGHT, BLACK);
    }
    if(length < 0){//yendo para la izquierda
        auxPos[X] = bar_pos[X] + BAR_LENGTH+ length/2;
        auxPos[Y] =  bar_pos[Y];
        printOnScreen(auxPos, BAR_LENGTH, BAR_HEIGHT, BLACK);
    }
    
    
}



void handleBarMov(){
    //barHitWall devuelve un int que representa que pared esta chocando
    int w = barHitWall();
    int key = key_pressed();
    if(key == RIGHT_ARROW){
        if(!(w == RIGHT)){
            bar_pos[X] += bar_vel;                     //muevo la barra para la derecha
        }
    }
    //if(left_arrow_pressed()){
    if(key== LEFT_ARROW){
        if(!(w == LEFT)){      
             bar_pos[X]  -= bar_vel;                     //muevo la barra para la izquierda
        }
    } 

    if(key == LEAVE_KEY){
        goToTerminal = true;
    }
}

void handleBallMov(void){
    //si pega contra una pared
    walls wall;
    barSides bar_side;
    ballHitBlock();            // se fija en donde y en que bloque pego
    if( (wall = ballHitWall()) ){   //NONE = 0 entonces devuelve FALSE
        
        switch(wall){
            case FLOOR:
            case LLCORNER:
            case LRCORNER:
                lives -=1; 
                print_bar(bar_pos, BLACK);
                ball.pos[X]=SCREEN_WIDTH/2;
                ball.pos[Y]=SCREEN_HEIGHT/2;
                ball.dir= D;
                bar_pos[X] = SCREEN_WIDTH/2;
                return;
            break;
            case LEFT:    
            case RIGHT:
            case UPPER:
            case URCORNER:
            case ULCORNER:
                invertDirection(wall);
            break;
        }
    }
    //si pega contra un bloque
    else if(block[0] != NO_BLOCK){      
        blocks.matrix[block[1]][block[0]]=0;
        invertDirection(block[2]);
    }
    //Si pega en la barra
    else if( (bar_side = ballHitBar()) ){
        ballHitBarChangeDireccion(bar_side);
    }
    ballMove();
}

/*typedef enum barSides{N = 0, L, R, UL, UM, UR} barSides;      
             ____________________________________ bar_Ycord[0]
            |___________|_____-______|___________| <-bar      __ bar_Ycord[1]
     bar_Xcord[0]  bar_Xcord[1]  bar_Xcord[2]  bar_Xcord[3]
                               ^
                               |
                            bar_pos
*/
barSides ballHitBar(){
    int bar_Xcord[]={bar_pos[X] - BAR_LENGTH/2, bar_pos[X] - BAR_LENGTH/6, bar_pos[X] + BAR_LENGTH/6, bar_pos[X] + BAR_LENGTH/2};
    int bar_Ycord[] = {bar_pos[Y] - BAR_HEIGHT / 2, bar_pos[Y] + BAR_HEIGHT / 2 };
    int nextPos[2];
    ballNextPos(nextPos);
    int LLSquare[2];
    int URSquare[2];
    
    makeSquare(LLSquare, bar_Xcord[0], bar_Ycord[1]);  
    makeSquare(URSquare, bar_Xcord[3], bar_Ycord[0]);

    if(!insideSquare(nextPos, LLSquare , URSquare)){
        return N;
    }
    else{
        //dentro de la primer parte de la barra
        
        makeSquare(LLSquare, bar_Xcord[0], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[1], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            if(ballBetween(ball.pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return L;
            }
            return UL;
        }
        //dentro de la segunda parte de la barra

        makeSquare(LLSquare, bar_Xcord[1], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[2], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            return UM;
        }
        //dentro de la TERCER parte de la barra
        
        makeSquare(LLSquare, bar_Xcord[2], bar_Ycord[1]);  
        makeSquare(URSquare, bar_Xcord[3], bar_Ycord[0]);

        if(insideSquare(nextPos, LLSquare, URSquare)){
            if(ballBetween(ball.pos[Y], bar_Ycord[0], bar_Ycord[1])){
                return R;
            }
            return UR;
        }
    }
    return N;
}

void makeSquare(int * square, int x, int y){
    square[X] = x;
    square[Y] = y;
    return;
}

int ballBetween(int auxPos, int y1, int y2){
    if(auxPos <= y2 && auxPos >= y1){
        return 1;
    }
    return 0;
}

//la pos de la pelota, punto de abajo a la izquierda y arriba a la derecha del cuadrado
int insideSquare(int * auxPos, int * LLSquare, int * URSquare){
    if(ballBetween(auxPos[X],LLSquare[X], URSquare[X]) && ballBetween(auxPos[Y], URSquare[Y], LLSquare[Y])){
        return 1;
    }
    return 0;
}

void print_blocks(){
    int x;
    int y;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j <R_BLOCKS ; j++){
            x=i;
            y=j;
            matrixToXY(&x, &y);
            if( blocks.matrix[j][i] == 1){
                print_block( x ,y,AQUA);
            }else{
               print_block( x , y,BLACK);
            }
        }
    }
}

void ballHitBarChangeDireccion(barSides side){
    //enum ballDirec{LU, U, RU, RD,D, LD}ballDirec
    switch(side){
        case L:
            ball.dir = LD;
            break;
        case R:
            ball.dir = RU;
            break;
        case UL:
            ball.dir = LU;
            break;
        case UM:
            ball.dir = U;
            break;
        case UR:
            ball.dir = RU;
            break;
    }
}

void ballMove(){
    ballNextPos(ball.pos);
}

void ballNextPos(int * auxPos){
    auxPos[X] = ball.pos[X];
    auxPos[Y] = ball.pos[Y];
    switch(ball.dir){
        case LU:
            auxPos[X] -= ( ball.vel * 0.7071); 
            auxPos[Y] -= ( ball.vel * 0.7071);
            break;
        case U:
            auxPos[Y] -= ball.vel;  
            break;
        case RU:
            auxPos[X] += ( ball.vel * 0.7071); 
            auxPos[Y] -= ( ball.vel * 0.7071);
            break;
        case RD:
            auxPos[X] += ( ball.vel * 0.7071); 
            auxPos[Y] += ( ball.vel * 0.7071);
            break;
        case D: 
            auxPos[Y] += ball.vel;
            break;
        case LD:
            auxPos[X] -= ( ball.vel * 0.7071); 
            auxPos[Y] += ( ball.vel * 0.7071);
            break;
    }
    return;
}
 

void invertDirection(walls wall){
    switch(wall){
        case ULCORNER:
            ball.dir = RD;
        break;
        case URCORNER:
            ball.dir = LD;
        break;
        case LLCORNER:
            ball.dir = RU;
        break;
        case LRCORNER:
            ball.dir = LU;
        break;
        case LEFT:
            if(ball.dir == LU){
                    ball.dir = RU;
            }
            else if( ball.dir == LD){
                ball.dir = RD;
            }
        break;
        case RIGHT:
            if(ball.dir == RU){
                ball.dir = LU;
            }else if(ball.dir == RD){
                ball.dir = LD;
            }
        break;
        case UPPER:
            switch(ball.dir){
                case LU:
                    ball.dir = LD;
                break;
                case RU:
                    ball.dir = RD;
                break;
                case U:
                    ball.dir = D;
                break;
            }
        break;
        //FLOOR SOLO PASA CON LOS BLOQUES(la parte de arriba)
        case FLOOR:
            switch(ball.dir){
                case LD:
                    ball.dir = LU;
                break;
                case RD:
                    ball.dir = RU;
                break;
                case D:
                    ball.dir = U;
                break;
            }
        break;

    }
}



//implementar CORNERS
walls ballHitWall(){
    int auxPos[2];
    ballNextPos(auxPos);
    if(auxPos[X]   <= BALL_RADIO){
        return LEFT;
    }else if(auxPos[Y]   <= BALL_RADIO ){
        return UPPER;
    }else if(auxPos[X] + BALL_RADIO >= SCREEN_WIDTH ){
        return RIGHT;
    
    }else if(auxPos[Y] + BALL_RADIO >= BAR_YPOS+BAR_HEIGHT){
        return FLOOR;
    }
    return NONE;
}

walls barHitWall(){
    if( ( bar_pos[X]+ bar_vel + (BAR_LENGTH /2) ) >= SCREEN_WIDTH){
        return RIGHT;
    }else if(bar_pos[X] -bar_vel <= BAR_LENGTH/2){
        return LEFT;
    }
    return NONE;
}

void ballHitBlock(){
    walls auxWall;
    for(int i = 0; i < C_BLOCKS ; i++){
        for(int j = 0; j < R_BLOCKS; j++){
            if(blocks.matrix[j][i]==1){
                auxWall = ballTouchingWall(i, j);
                if(auxWall){
                    block[0]=i;
                    block[1]=j;
                    block[2]=auxWall;
                    return;
                }
            }       
        }
    }
    block[0]= NO_BLOCK;
    block[1]=NO_BLOCK;
    block[2]=NO_BLOCK;
    return;
}


walls ballTouchingWall(int c, int r){
    int a ;
    int nextPos[2];
    ballNextPos(nextPos);
    if(ballBetweenYSides(nextPos, c, r)){
        if(ballBetweenXSides(nextPos, c, r)){
            blocks.left -=1;
            if( ballBetweenXSides(ball.pos, c, r) ){
                if(ball.dir == U || ball.dir == LU || ball.dir == RU){
                
                    return UPPER;//en verdad es la parte de abajo del bloque pero se comporta como la pared de arriba
                }
                if(ball.dir == D || ball.dir == LD || ball.dir == RD){
                    return FLOOR; //en verdad esta tocando la parte de arriba pero se comporta como piso
                }
            }
            if(ballBetweenYSides(ball.pos, c, r)){
            
                if(ball.dir == LU || ball.dir == LD){
                    return LEFT;
                }
                if(ball.dir == RU || ball.dir == RD){
                    return RIGHT; 
                }
            }
            if( !ballBetweenYSides(ball.pos, c, r) && !ballBetweenXSides(ball.pos, c, r)){
            
                switch(ball.dir){
                    case LU:
                        return ULCORNER;    
                    break;
                    case RU:
                        return URCORNER;
                    break;
                    case LD:
                        return  LLCORNER;
                    break;
                    case RD:
                        return LRCORNER;
                    break;
            
                }
            }
        }
    }
    return NONE;
}

int ballBetweenXSides(int * auxPos, int c, int r){
    int x1=(c* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION);
    int x2=( (c+1)* BLOCK_WIDTH + (c+1)* BLOCK_XSEPARATION );

    return ballBetween(auxPos[X], x1, x2 );
}

int ballBetweenYSides(int * auxPos, int c, int r){
    int lowerSideOfBlock = (r+1) * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION;
    int upperSideOfBlock =  r * BLOCK_HEIGHT + (r+1) * BLOCK_YSEPARATION;

    return ballBetween(auxPos[Y], upperSideOfBlock, lowerSideOfBlock); 
}


int finishGame(int time_past){
        clearConsole();
        int init;
        getBpp(&init);
        setSize(init*3);
    if(blocks.left == 0){
        printfColorAt("Congratulations you've won!!",RED,BLACK,90,100);
        printfColorAt("It took you %d seconds",RED,BLACK,115,120,time_past);
           
    }else{

        printfColorAt("Better luck next time!",RED,BLACK,90,100);
        printfColorAt("Time: %d seconds",RED,BLACK,115,120,time_past);
    }
        printfColorAt("Press x to restart or q to quit",BLUE,BLACK,50,140,time_past);
        setSize(init);
        char c;
        while((c=readKey())!='x'&& c!='q');
        clearConsole();
        if(c=='x')
         return 1;
    return 0;
}

void print_ball(int * ball_pos,int color){
    printOnScreen(ball_pos,BALL_RADIO*2,BALL_RADIO*2,color);
}

void print_bar(int * bar_pos,int color){
    printOnScreen(bar_pos,BAR_LENGTH,BAR_HEIGHT,color);

}

void print_block(int x,int y,int color){
    int pos[]= {x, y};

    printOnScreen(pos,BLOCK_WIDTH,BLOCK_HEIGHT,color);

}

int stopKeyPressed(){

    return goToTerminal;
}


bool limitInput(char ch){

    if(keyBufferFront-3 > keyBufferBack){
            return ch == KeyBuffer[keyBufferFront-1] && ch == KeyBuffer[keyBufferFront-2] && ch == KeyBuffer[keyBufferFront-3];
    }
    else if(keyBufferBack > keyBufferFront){
        
        if(keyBufferFront -3> 0 ){
            return ch == KeyBuffer[keyBufferFront-1] && ch == KeyBuffer[keyBufferFront-2] && ch == KeyBuffer[keyBufferFront-3];
        }
    }

    return false;
}

void parseKeyboard(){
    if(keyBufferFront + 1 == keyBufferBack )
        keyBufferBack++;
        
    int temp = readKey();

    if((temp == LEFT_ARROW || temp == RIGHT_ARROW || temp == LEAVE_KEY) && !limitInput(temp))
        KeyBuffer[keyBufferFront++ % 200] = temp;

}

int key_pressed(){


    if(keyBufferFront == keyBufferBack)
        return -1;
        
    return KeyBuffer[keyBufferBack++ % 200];


}
void table(){
    printOnScreen(info,SCREEN_WIDTH,SCREEN_HEIGHT-info[1],YELLOW);
    printfColorAt("Blocks left :",BLACK,YELLOW,150,info[1]);
    printfColorAt("Lives :",BLACK,YELLOW,450,info[1]);
    printfColorAt("Time :",BLACK,YELLOW,800,info[1],time.tick/18);
    tableData();
}

void tableData(){
    if(blocks.left==9)
        printfColorAt(" ",YELLOW,YELLOW,268,info[1]);    

    printfColorAt("%d",BLACK,YELLOW,260,info[1],blocks.left);
    printfColorAt("%d",BLACK,YELLOW,520,info[1],lives);
    printfColorAt("%d",BLACK,YELLOW,850,info[1],time.tick/18);
}


void manageSound(uint64_t realTick){


        uint64_t tick = realTick % 1171;

        switch(tick){
            case 0:{
                playSound(660);
                break;
            }
            case 2:{
                stopSound();
                break;
            }
            case 5:{
                playSound(660);
                break;
            }
            case 7:{
                stopSound();
                break;
            }
            case 13:{
                playSound(500);
                break;
            }
            case 15:{
                stopSound();
                break;
            }
            case 21:{
                playSound(510);
                break;
            }
            case 23:{
                stopSound();
                break;
            }
            case 25:{
                playSound(660);
                break;
            }
            case 27:{
                stopSound();
                break;
            }
            case 33:{
                playSound(770);
                break;
            }
            case 35:{
                stopSound();
                break;
            }
            case 46:{
                playSound(380);
                break;
            }
            case 48:{
                stopSound();
                break;
            }
            case 60:{
                playSound(510);
                break;
            }
            case 62: stopSound();break;
            case 71:playSound(380);break;
            case 73:stopSound();break;
            case 81:playSound(320);break;
            case 83:stopSound();break;
            case 93: playSound(440);break;
            case 95: stopSound();break;
            case 101: playSound(480);break;
            case 102: stopSound(); break;
            case 108: playSound(450); break;
            case 110:stopSound();break;
            case 113: playSound(430);break;
            case 115: stopSound(); break;
            case 121: playSound(380); break;
            case 123: stopSound();break;
            case 127: playSound(660);break;
            case 129: stopSound(); break;
            case 133: playSound(760);break;
            case 134: stopSound();break;
            case 137: playSound(860);break;
            case 139: stopSound(); break;
            case 145: playSound(700); break;
            case 147: stopSound();break;
            case 150: playSound(760);break;
            case 151: stopSound();break;
            case 158: playSound(660); break;
            case 159: stopSound();break;
            case 165: playSound(520); break;
            case 166: stopSound(); break;
            case 169: playSound(580);break;
            case 170: stopSound(); break;
            case 173: playSound(480); break;
            case 174: stopSound(); break;
            case 184: playSound(510); break;
            case 186: stopSound(); break;
            case 195: playSound(380); break;
            case 197: stopSound(); break;
            case 205: playSound(320); break;
            case 207: stopSound(); break;
            case 217: playSound(440); break;
            case 219: stopSound(); break;
            case 225: playSound(480); break;
            case 226: stopSound(); break;
            case 232: playSound(450); break;
            case 234: stopSound(); break;
            case 237: playSound(430); break;
            case 235: stopSound(); break;
            case 241: playSound(380); break;
            case 243: stopSound(); break;
            case 247: playSound(660); break;
            case 249: stopSound(); break;
            case 253: playSound(760); break;
            case 254: stopSound(); break;
            case 257: playSound(760); break;
            case 258: stopSound(); break;
            case 261: playSound(860); break;
            case 263: stopSound(); break;
            case 269: playSound(700); break;
            case 270: stopSound(); break;
            case 273: playSound(760); break;
            case 274: stopSound(); break;
            case 281: playSound(660); break;
            case 282: stopSound(); break;
            case 288: playSound(520); break;
            case 289: stopSound(); break;
            case 292: playSound(580); break;
            case 293: stopSound(); break;
            case 296: playSound(480); break;
            case 297: stopSound(); break;
            case 307: playSound(500); break;
            case 309: stopSound(); break;
            case 315: playSound(760); break;
            case 317: stopSound(); break;
            case 319: playSound(720); break;
            case 321: stopSound(); break;
            case 324: playSound(680); break;
            case 326: stopSound(); break;
            case 329: playSound(620); break;
            case 332: stopSound(); break;
            case 338: playSound(650); break;
            case 341: stopSound(); break;
            case 347: playSound(380); break;
            case 349: stopSound(); break;
            case 352: playSound(430); break;
            case 354: stopSound(); break;
            case 360: playSound(430); break;
            case 362: stopSound(); break;
            case 365: playSound(500); break;
            case 367: stopSound(); break;
            case 373: playSound(430); break;
            case 375: stopSound(); break;
            case 378: playSound(500); break;
            case 380: stopSound(); break;
            case 382: playSound(570); break;
            case 384: stopSound(); break;
            case 388: playSound(500); break;
            case 390: stopSound(); break;
            case 396: playSound(760); break;
            case 398: stopSound(); break;
            case 400: playSound(720); break;
            case 402: stopSound();break;
            case 406: playSound(500); break;
            case 408: stopSound(); break;
            case 414: playSound(760); break;
            case 416: stopSound(); break;
            case 418: playSound(720); break;
            case 420: stopSound(); break;
            case 423: playSound(680); break;
            case 425: stopSound(); break;
            case 428: playSound(620); break;
            case 431: stopSound(); break;
            case 437: playSound(650); break;
            case 441: stopSound(); break;
            case 447: playSound(1020); break;
            case 448: stopSound(); break;
            case 454: playSound(1020); break;
            case 455: stopSound(); break;
            case 458: playSound(1020); break;
            case 459: stopSound(); break;
            case 465: playSound(380); break;
            case 466: stopSound(); break;
            case 472: playSound(500); break;
            case 474: stopSound(); break;
            case 500: playSound(760); break;
            case 502: stopSound(); break;
            case 504: playSound(720); break;
            case 506: stopSound(); break;
            case 509: playSound(680); break;
            case 511: stopSound(); break;
            case 514: playSound(620); break;
            case 517: stopSound(); break;
            case 523: playSound(650); break;
            case 526: stopSound(); break;
            case 532: playSound(380); break;
            case 534: stopSound(); break;
            case 537: playSound(430); break;
            case 539: stopSound(); break;
            case 542: playSound(500); break;
            case 544: stopSound(); break;
            case 560: playSound(430); break;
            case 562: stopSound(); break;
            case 565: playSound(500); break;
            case 567: stopSound(); break;
            case 569: playSound(570); break;
            case 571: stopSound(); break;
            case 579: playSound(585); break;
            case 581: stopSound(); break;
            case 590: playSound(550); break;
            case 592: stopSound(); break;
            case 600: playSound(500); break;
            case 602: stopSound(); break;
            case 609: playSound(380); break;
            case 611: stopSound(); break;
            case 617: playSound(500); break;
            case 619: stopSound(); break;
            case 625: playSound(500); break;
            case 627: stopSound(); break;
            case 630: playSound(500); break;
            case 632: stopSound(); break;
            case 638: playSound(500); break;
            case 640: stopSound(); break;
            case 646: playSound(760); break;
            case 648: stopSound(); break;
            case 650: playSound(720); break;
            case 652: stopSound(); break;
            case 655: playSound(680); break;
            case 657: stopSound(); break;
            case 660: playSound(620); break;
            case 663: stopSound(); break;
            case 669: playSound(650); break;
            case 672: stopSound(); break;
            case 678: playSound(380); break;
            case 680: stopSound(); break;
            case 683: playSound(430); break;
            case 685: stopSound(); break;
            case 688: playSound(500); break;
            case 690: stopSound(); break;
            case 696: playSound(430); break;
            case 698: stopSound(); break;
            case 701: playSound(500); break;
            case 703: stopSound(); break;
            case 705: playSound(570); break;
            case 707: stopSound(); break;
            case 711: playSound(500); break;
            case 713: stopSound(); break;
            case 719: playSound(760); break;
            case 721: stopSound(); break;
            case 723: playSound(720); break;
            case 725: stopSound(); break;
            case 728: playSound(680); break;
            case 730: stopSound(); break;
            case 733: playSound(620); break;
            case 736: stopSound(); break;
            case 742: playSound(650); break;
            case 746: stopSound(); break;
            case 752: playSound(1020); break;
            case 753: stopSound(); break;
            case 759: playSound(1020); break;
            case 760: stopSound(); break;
            case 763: playSound(1020); break;
            case 764: stopSound(); break;
            case 770: playSound(380); break;
            case 772: stopSound(); break;
            case 778: playSound(500); break;
            case 780: stopSound(); break;
            case 786: playSound(760); break;
            case 788: stopSound(); break;
            case 790: playSound(720); break;
            case 792: stopSound(); break;
            case 795: playSound(680); break;
            case 797: stopSound(); break;
            case 800: playSound(620); break;
            case 803: stopSound(); break;
            case 809: playSound(650); break;
            case 812: stopSound(); break;
            case 818: playSound(380); break;
            case 820: stopSound(); break;
            case 823: playSound(430); break;
            case 825: stopSound(); break;
            case 828: playSound(500); break;
            case 830: stopSound(); break;
            case 836: playSound(430); break;
            case 838: stopSound(); break;
            case 841: playSound(500); break;
            case 843: stopSound(); break;
            case 845: playSound(570); break;
            case 857: stopSound(); break; 
            case 865: playSound(585); break;
            case 867: stopSound(); break;
            case 866: playSound(550); break;
            case 868: stopSound(); break;
            case 876: playSound(500); break;
            case 878: stopSound(); break;
            case 885: playSound(380); break;
            case 887: stopSound(); break;
            case 893: playSound(500); break;
            case 895: stopSound(); break;
            case 901: playSound(500); break;
            case 903: stopSound(); break;
            case 906: playSound(500); break;
            case 908: stopSound(); break;
            case 914: playSound(500); break;
            case 915: stopSound(); break;
            case 918: playSound(500); break;
            case 920: stopSound(); break;
            case 926: playSound(500); break;
            case 927: stopSound(); break;
            case 934: playSound(500); break;
            case 936: stopSound(); break;
            case 939: playSound(580); break;
            case 941: stopSound(); break;
            case 948: playSound(660); break;
            case 950: stopSound(); break;
            case 953: playSound(500); break;
            case 955: stopSound(); break;
            case 961: playSound(430); break;
            case 963: stopSound(); break;
            case 966: playSound(380); break;
            case 968: stopSound(); break;
            case 980: playSound(500); break;
            case 981: stopSound(); break;
            case 984: playSound(500); break;
            case 986: stopSound(); break;
            case 992: playSound(500); break;
            case 993: stopSound(); break;
            case 1000: playSound(500); break;
            case 1002: stopSound(); break;
            case 1005: playSound(580); break;
            case 1007: stopSound(); break;
            case 1010: playSound(660); break;
            case 1012: stopSound(); break;
            case 1023: playSound(870); break;
            case 1025: stopSound(); break;
            case 1031: playSound(760); break;
            case 1033: stopSound(); break;
            case 1045: playSound(500); break;
            case 1046: stopSound(); break;
            case 1049: playSound(500); break;
            case 1051: stopSound(); break;
            case 1057: playSound(500); break;
            case 1058: stopSound(); break;
            case 1065: playSound(500); break;
            case 1067: stopSound(); break;
            case 1070: playSound(580); break;
            case 1072: stopSound(); break;
            case 1079: playSound(660); break;
            case 1081: stopSound(); break;
            case 1084: playSound(500); break;
            case 1086: stopSound(); break;
            case 1092: playSound(430); break;
            case 1094: stopSound(); break;
            case 1097: playSound(380); break;
            case 1099: stopSound(); break;
            case 1111: playSound(660); break;
            case 1113: stopSound(); break;
            case 1116: playSound(660); break;
            case 1118: stopSound(); break;
            case 1124: playSound(660); break;
            case 1126: stopSound(); break;
            case 1132: playSound(510); break;
            case 1134: stopSound(); break;
            case 1136: playSound(660); break;
            case 1138: stopSound(); break;
            case 1144: playSound(770); break;
            case 1146: stopSound(); break;
            case 1157: playSound(380); break;
            case 1159: stopSound(); break;
            default:{break;}
        }
    
    


}