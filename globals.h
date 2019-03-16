// ============================================
// The header file for general project settings
// Spring 2018 Gatech ECE2035
//=============================================
#ifndef GLOBAL_H
#define GLOBAL_H

// Include all the hardware libraries
#include "mbed.h"
#include "wave_player.h"
#include "MMA8452.h"
#include "uLCD_4DGL.h"
#include "SDFileSystem.h"

// Declare the hardware interface objects
extern uLCD_4DGL uLCD;      // LCD Screen
extern SDFileSystem sd;     // SD Card
extern Serial pc;           // USB Console output
extern MMA8452 acc;       // Accelerometer
extern DigitalIn button1;   // Pushbuttons
extern DigitalIn button2;
extern DigitalIn button3;
extern AnalogOut DACout;    // Speaker
extern PwmOut speaker;
extern wave_player waver;

// === [define the macro of error heandle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        pc.printf("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood
#define ERROR_MEH -1 // This is how errors are done
#define MAP_HEIGHT 50
#define MAP_WIDTH 50
#define SPEED 2
#define BURGUNDY 0x800020
#define ORANGE      0xFFA500 //orange


// Graphics sprites for different characters
 const char image [11*11] = 
 {'w','w','w','w','w','w','w','w','w','w','w',
 'w','w','w','w','w','w','w','w','w','w','w',
 'w','b','w','b','w','w','w','b','w','b','w',
 'w','w','b','w','w','w','w','w','b','w','w',
 'w','b','w','b','w','w','w','b','w','b','w',
 'w','w','w','w','w','w','w','w','w','w','w',
 'w','b','w','w','w','w','w','w','w','b','w',
 'w','w','b','b','w','w','w','b','b','w','w',
 'w','w','w','b','b','b','b','b','w','w','w',
 'w','w','w','w','w','w','w','w','w','w','w'};
 
const char masterSprite [11*11]=  {
'b','b','b','g','g','g','g','b','b','b','b',
'b','b','g','g','g','g','g','g','b','b','b',
'b','g','g','g','g','g','g','g','g','g','b',
'g','b','b','b','b','b','b','b','b','b','g',
'g','b','o','w','w','o','w','w','o','g','b',
'b','o','o','w','o','o','o','w','o','o','g',
'b','o','o','o','o','o','o','o','o','o','g',
'g','b','o','o','b','b','b','o','o','b','g',
'g','g','o','b','g','g','g','b','b','g','g',
'b','b','g','b','g','b','g','b','g','b','b',
'b','b','g','b','g','g','g','b','g','b','b'};

const char chocolate[11*11] = {
'b','b','d','d','d','d','d','d','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','d','d','d','d','d','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','d','d','d','d','d','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','l','l','d','l','l','d','b','b',
'b','b','d','d','d','d','d','d','d','b','b'
};




#endif //GLOBAL_H