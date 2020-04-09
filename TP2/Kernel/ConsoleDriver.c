#include "include/ConsoleDriver.h"
#include <VideoDriver.h>
#include <String.h>
#include <Debugger.h>
#include <font.h>

/***************************************************************/
/*                         CONSTANTES                          */
/***************************************************************/

#define MAX_BUFFER_SIZE (10000)

#define DEFAULT_FONT_COLOR (0xFFFFFF)
#define DEFAULT_BACKGROUND_COLOR (0x000000)

/***************************************************************/
/*                          VARIABLES                          */
/***************************************************************/

static int charHeight;
static int charWidth;
static int screenHeight;
static int screenWidth;

static ColorChar Buffer[MAX_BUFFER_SIZE];
static int currPosition = 0;
static int previusCurrPosition = 0;
static int currentRows = 0;


/***************************************************************/
/*                         Declaraciones                       */
/***************************************************************/

void reflectBufferChangesToDisplay();

int countRepetitionsOfColorString(ColorChar * str, char ch);
int strlenColorString(ColorChar* str);
void appendColorString(ColorChar * src, ColorChar * dest, int bufferSize);
void removeColorString(ColorChar * str, int pos);
int findLastReferenceOfColorString(ColorChar * buffer, int initialPosition, char element);


/***************************************************************/
/*                      Funciones Publicas                     */
/***************************************************************/

void initializeConsoleDriver(int charHeight_,int charWidth_, int screenHeight_, int screenWidth_){
    charHeight = charHeight_;
    charWidth = charWidth_;
    screenHeight = screenHeight_;
    screenWidth = screenWidth_;

}



void printLine(char * string){
    int lenght = strlen(string);

    ColorChar temp[lenght];
    int i;

    for( i = 0 ; string[i]!=0 ; i++){
        temp[i].ch = string[i];
        temp[i].fontColor = DEFAULT_FONT_COLOR;
        temp[i].backgroundColor = DEFAULT_BACKGROUND_COLOR;
    }

    temp[i].ch = 0;
    temp[i].fontColor = DEFAULT_FONT_COLOR;
    temp[i].backgroundColor = DEFAULT_BACKGROUND_COLOR;

    printLineColor(temp);
}



void printLineColor(ColorChar * string){

    for( previusCurrPosition = currPosition ; 
            currPosition < MAX_BUFFER_SIZE && string[currPosition - previusCurrPosition].ch != 0;
            currPosition++){
        if(string[currPosition-previusCurrPosition].ch == '\n')
            currentRows++;
        Buffer[currPosition] = string[currPosition-previusCurrPosition];
    }

    Buffer[currPosition].ch = 0;

    currentRows += findLastReferenceOfColorString(Buffer,currPosition-2,'\n') * charWidth / screenWidth;

    reflectBufferChangesToDisplay();
}

void printLineColorAt(ColorChar * string){
    for(int i=0;string[i].ch!=0;i++){
        drawChar(string[i].x,string[i].y,string[i].ch,string[i].fontColor,string[i].backgroundColor);
    }
}
void printChar(char ch){

    ColorChar temp;
    temp.ch = ch;
    temp.backgroundColor = DEFAULT_BACKGROUND_COLOR;
    temp.fontColor = DEFAULT_FONT_COLOR;

    printCharColor(temp);    
}

void printCharColor(ColorChar ch){

    if(ch.ch == '\n'){
        currentRows += 1 + findLastReferenceOfColorString(Buffer,currPosition-2,'\n') * charWidth / screenWidth;
        previusCurrPosition = currPosition;
    }

    Buffer[currPosition] = ch;
    currPosition += 1;
    Buffer[currPosition].ch = 0;
    
    reflectBufferChangesToDisplay();
}

void clearConsole(){
    currentRows = 0;
    currPosition = 0;
    previusCurrPosition = 0;

    Buffer[currPosition].ch = 0;
    Buffer[currPosition].fontColor = DEFAULT_FONT_COLOR;
    Buffer[currPosition].backgroundColor = DEFAULT_BACKGROUND_COLOR;

    for(int x = 0 ; x <= screenWidth; x+= charWidth)
        for(int y = 0 ; y <= screenHeight; y+= charHeight)
            drawChar(x,y,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);    
}


void removeLastChar(){
    if(currPosition > 0){
        Buffer[currPosition].ch = 0;
        currPosition--;

        if(Buffer[currPosition].ch == '\n')
            currentRows--;

        Buffer[currPosition].ch = ' ';
        Buffer[currPosition].fontColor = DEFAULT_FONT_COLOR;
        Buffer[currPosition].backgroundColor = DEFAULT_BACKGROUND_COLOR;

        reflectBufferChangesToDisplay();
    }
}



/***************************************************************/
/*                    Funciones Privadas                       */
/***************************************************************/

void reflectBufferChangesToDisplay(){

    int rows = 1+ currentRows;
    int a = findLastReferenceOfColorString(Buffer,currPosition-2,'\n') * charWidth;
    int extrarows = a/ screenWidth;
        

        int x = 0, y = rows + extrarows;

        if(Buffer[currPosition-1].ch == '\n' || !(a % screenWidth) ){
            for(int tempx = 0; tempx < a ; tempx += charWidth)
                drawChar(tempx,screenHeight - charHeight * (1),' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);
        }

        for(int i = 0 ; Buffer[i].ch != 0 ; i++){
            if(Buffer[i].ch == '\n' || x >= screenWidth){

                if(screenHeight - charHeight * y >=0){
                    for(int tempx = x; tempx < screenWidth ; tempx += charWidth)
                            drawChar(tempx,screenHeight - charHeight * y,' ',DEFAULT_FONT_COLOR,DEFAULT_BACKGROUND_COLOR);

                }

                if(x >= screenWidth)
                    i--;

                y--;
                x = 0;
            }else if (screenHeight - charHeight * y >=0 ){
                drawChar(x,screenHeight - charHeight * y ,Buffer[i].ch,Buffer[i].fontColor,Buffer[i].backgroundColor);
                x+= charWidth;
            }
        }

}

int strlenColorString(ColorChar* str){
    int i = 0;
    while(str[i].ch!=0){
        i++;
    }
    return i;
}

int findLastReferenceOfColorString(ColorChar * buffer, int initialPosition, char element){
    int counter = 0;
    for(int i = initialPosition ; i >= 0 && buffer[i].ch != element;i--){
        counter++;
    }
    return counter;
}

void removeColorString(ColorChar * str, int pos){
    for(int i = pos; str[i].ch != 0 ; i++ ){

        str[i] = str[i+1];

    }
}


void appendColorString(ColorChar * src, ColorChar * dest, int bufferSize){
    int base = strlenColorString(dest);
    int i;
	for( i = 0 ; base + i-1 < bufferSize && src[i].ch != 0 ; i++){
		dest[base + i] = src[i];
        dest[base + i+1].ch = 0;

	}
}

int countRepetitionsOfColorString(ColorChar * str, char ch){
    int count = 0;
	for( int i = 0 ; str[i].ch != 0; i++)
		if(str[i].ch == ch)
			count++;

	return count;
}
