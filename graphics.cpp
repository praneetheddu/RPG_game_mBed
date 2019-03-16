#include "graphics.h"
#include "globals.h"

  

#define YELLOW      0xFFFF00
#define BROWN       0xD2691E
#define DIRT        BROWN
#define w           WHITE
#define b           BLACK
#define ORANGE      0xe68a00 //orange
#define g           GREEN
#define DARKBROWN   0x331a00 //dark brown
#define LIGHTBROWN  0x804000 //chocalate brown
#define LIGHTORANGE 0xffad33 //Light Orange 
#define BURGUNDY    0x800020 //BURGUNDY
#define LIGHTGREEN  0x32CD32 //LIGHT GREEN     
#define LIGHTORANGEE 0xffcc80//LIGHT ORANGE 
#define DGREEN         0x096b1e      
#define MGREEN          0x23af41         

//Intialize colors and draw images
void draw_img(int u, int v, const char* img)
{

    int colors[11*11];

    for (int i = 0; i < 11*11; i++)
    //for (int i = 0; i < 14*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'w') colors[i] = WHITE;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == 'o') colors[i] = ORANGE;
        else if (img[i] == 'g') colors[i] = GREEN;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'd') colors[i] = DGREY;
        else if (img[i] == 'z') colors[i] = LIGHTORANGE;
        else if (img[i] == 'r') colors[i] = RED;
        else if (img[i] == 't') colors[i] = LIGHTGREEN;
        else if (img[i] == 'c') colors[i] = LIGHTORANGEE;
        else if (img[i] == 'x') colors[i] = DGREEN;
        else if (img[i] == 'v') colors[i] = MGREEN;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}
void draw_player(int u, int v, int key)
{
    const char* zelda = {
        "bbbgggggbbb"
        "YbgrrrrrgbY"
        "YbgrrrrrgbY"
        "YbrYgYgYrbY"
        "YYrYrYrYrYY"
        "YYrYYYYYrYY"
        "bYYYYrYYYYb"
        "bbgYYYYYgbb"
        "bbggrrrggbb"
        "bbrrrgrrrbb"
        "bbggrrrggbb"
        };
        
    
   draw_img(u, v, zelda);
}

void draw_player_side(int u, int v)
{
    const char* zelda = {
        "bbbbggggbbb"
        "bbbbrrrrgbb"
        "bbbbYYYYrbb"
        "bbbbrYYYrbb"
        "bbbbYYYYrbb"
        "bbbbYYYYYbb"
        "bbbbYYYYgbb"
        "bbbbgggggbb"
        "bbbbrrrggbb"
        "bbbbgggrrbb"
        "bbbbrrrrggbb"
        };
        
    
   draw_img(u, v, zelda);
}
void draw_player2(int u, int v, int key) {
    
    const char* zelda = {
        "bbbgggggbbb"
        "YbgrrrrrgbY"
        "YbgrrrrrgbY"
        "YbrYgYgYrbY"
        "YYrYrYrYrYY"
        "YYrYYYYYrYY"
        "bYYYYrYYYYb"
        "bbgYYYYYgbb"
        "bbggrrrggbb"
        "bbrrrgrrrbb"
        "bbggrrrggbb"
        };
        
        int colors[11*11];

    for (int i = 0; i < 11*11; i++)
 
    {
        if (zelda[i] == 'R') colors[i] = RED;
        else if (zelda[i] == 'Y') colors[i] = RED;
        else if (zelda[i] == 'w') colors[i] = WHITE;
        else if (zelda[i] == 'G') colors[i] = GREEN;
        else if (zelda[i] == 'D') colors[i] = DIRT;
        else if (zelda[i] == 'o') colors[i] = ORANGE;
        else if (zelda[i] == 'g') colors[i] = GREEN;
        else if (zelda[i] == '5') colors[i] = LGREY;
        else if (zelda[i] == '3') colors[i] = DGREY;
        else if (zelda[i] == 'd') colors[i] = DGREY;
        else if (zelda[i] == 'z') colors[i] = LIGHTORANGE;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}
        
void draw_chocolate(int u, int v) {
    const char* choc = {
        "bbbDDDDDbbb"
        "bb5555555bb"
        "bb5DDDDD5bb"
        "bbb5bbb5bbb"
        "bbb5bbb5bbb"
        "bb5bbbbb5bb"
        "b5r5rrrrr5b"
        "b5r5rrrrr5b"
        "b5rrrrrrr5b"
        "b5rrr55rrrb"
        "b555555555b"
        };
    draw_img(u,v,choc);
    wait_us(250); // Recovery time!
} 

void draw_dragonball1(int u, int v) {
    const char* dragon1 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzzzzzzob"
    "byozzrzzzob"
    "byozzzzzzob"
    "bbozzzzzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
  };
 
    draw_img(u,v,dragon1);
    wait_us(250); // Recovery time!     
}
void draw_dragonball2(int u, int v) {
    const char* dragon2 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzrzzzzob"
    "byozzzzzzob"
    "byozzzrzzob"
    "bbozzzzzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
    };
    draw_img(u,v,dragon2);
    wait_us(250); // Recovery time!     
}

void draw_dragonball3(int u, int v) {
    const char* dragon3 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzzrzzzob"
    "byozzzzzzob"
    "byozrzzzzob"
    "bbozzzrzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
    };
    draw_img(u,v,dragon3);
    wait_us(250); // Recovery time!     
}
void draw_dragonball4(int u, int v) {
    const char* dragon3 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzzrzzzob"
    "byozzzzzzob"
    "byozrzzzzob"
    "bbozzzrzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
    };
    draw_img(u,v,dragon3);
    wait_us(250); // Recovery time!     
}

void draw_dragonball5(int u, int v) {
    const char* dragon3 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzzrzzzob"
    "byozzzzzzob"
    "byozrzzzzob"
    "bbozzzrzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
    };
    draw_img(u,v,dragon3);
    wait_us(250); // Recovery time!     
}

void draw_dragonball6(int u, int v) {
    const char* dragon3 = {
    "bbbyyyzzbbb"
    "bbyyzzzzobb"
    "byywzzzzzob"
    "bywzzzzzzob"
    "bywzzrzzzob"
    "byozzzzzzob"
    "byozrzzzzob"
    "bbozzzrzobb"
    "bbooooooobb"
    "bbbooooobbb"
    "bbbbbbbbbbb"
    };
    draw_img(u,v,dragon3);
    wait_us(250); // Recovery time!     
}
void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}


const char* wall = {
    "5d55555bdd5"
    "555555dbdd5"
    "dddd555b555"
    "dddddd5b55d"
    "dddddd5b55d"
    "bbbbbbbbbbb"
    "55555555555"
    "55555555555"
    "5dd55d555dd"
    "555d55dd5dd"
    "ddddddddddd"
    };
    
//    draw_img(u,v,wall);
//    wait_us(250); // Recovery time!  


void draw_master(int u, int v) {
        int colors[11*11];

    for (int i = 0; i < 11*11; i++)
    {
        if (masterSprite[i] == 'R') colors[i] = RED;
        else if (masterSprite[i] == 'Y') colors[i] = YELLOW;
        else if (masterSprite[i] == 'w') colors[i] = WHITE;
        else if (masterSprite[i] == 'G') colors[i] = GREEN;
        else if (masterSprite[i] == 'D') colors[i] = DIRT;
        else if (masterSprite[i] == 'o') colors[i] = ORANGE;
        else if (masterSprite[i] == 'g') colors[i] = GREEN;
        else if (masterSprite[i] == '5') colors[i] = LGREY;
        else if (masterSprite[i] == '3') colors[i] = DGREY;
        else if (masterSprite[i] == 'd') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
   wait_us(250); // Recovery time!

} 
void draw_plant(int u, int v)
{
   const char* plant = {
       "bbbbggbbbbb"
       "bbbxxvgbbbb"
       "bbxvvvvgbbb"
       "bxvvvvvvgbb"
       "xxvvvvvvvgb"
       "bxvvvvvvxbb"
       "bbxvvvvxbbb"
       "bbbxvvvxbbb"
       "bbbbDDbbbbb"
       "bbbbDDbbbbb"
       "bbbDDDDbbbb"
       "bbDDDDDDbbb"
       };
        draw_img(u,v,plant);
       wait_us(250);

}

void draw_door(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+8, v+8, BROWN);
    uLCD.filled_circle(u+5, v+6,2, YELLOW);
}

void draw_tree(int u, int v) 
{   
    uLCD.filled_rectangle(u+2, v+2,u + 7, v + 7, BROWN);
    uLCD.filled_circle(u, v, 3, GREEN);
}    
void draw_upper_status()
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);
    
    // Add other status info drawing code here
    //draw coordinates

    
}

void draw_openDoor(int u, int v) {
    uLCD.line(u, v, u+6, v+6, BROWN);
}

void draw_upper_back(int health) {
    uLCD.filled_rectangle(0,9,127,0,BURGUNDY);
    uLCD.filled_rectangle(64,9,127,0,GREEN);
    uLCD.filled_rectangle(64,9,64 + (127 % (health+27)/2),0,RED);
}

void draw_lower_back(int cases, int chocCounter) {
 //   if (cases < 0) {
//    uLCD.filled_rectangle(0, 127, 127, 117, YELLOW);
//    }
    //int counter = 6;
    draw_dragonball1(0,116);
    uLCD.textbackground_color(BLACK);
    uLCD.color(GREEN);
    uLCD.locate(2,15);
    uLCD.printf(": %d", cases);
    uLCD.locate(7,15);
    draw_chocolate(57,116);
    uLCD.locate(10,15);
    uLCD.printf(": %d", chocCounter);
    //for omnipotent, make the lower screen yellow and print omnipotent
    
    if (cases == 7) {
        uLCD.filled_rectangle(0, 127, 127, 117, RED);
        wait(0.5);
        uLCD.filled_rectangle(0, 127, 127, 117, ORANGE);
        wait(0.5);
        uLCD.filled_rectangle(0, 127, 127, 117, RED);
        wait(0.5);
        uLCD.filled_rectangle(0, 127, 127, 117, ORANGE);
        wait(0.5);
    }
    
}
void draw_lower_status()
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
}
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, BLUE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, BLUE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, BLUE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, BLUE); // Right
}

void draw_fire(int u, int v) {

const char* fire = {
    "bbbbrbrbbbb"
    "bbbrbbrbbrb"
    "bbbbbbrbbbb"
    "bbbbbbrrbbb"
    "bbbbbrrrbbb"
    "bbbbrrrrbbb"
    "bbbbrorrrbb"
    "bbbroooorbb"
    "bbbroYYrbb"
    "bbbroYoobbb"
    "bbbroYoobbb"
    "bbbbrorbbbb"
};
    draw_img(u,v,fire);
    wait_us(250);
}
void draw_portal(int u, int v) {
    const char* portal = {
    "bbbbwtwbbbb"
    "bbbwtttwbbb"
    "bbbwtttwbbb"
    "bbwwtggwwbb"
    "bbwtgggwwbb"
    "bwttgggttwb"
    "bwwtgYgtwbb"
    "bbwwtggtwbb"
    "bbwwttgtwbb"
    "bbbwttYwbbb"
    "bbbbwtwbbbb"
};
    draw_img(u,v,portal);
    wait_us(250);
    }
void draw_bolder(int u, int v) {
    const char* bolder = {
        "bbbbdddbbbb"
        "bbbdd5ddbbb"
        "bbdd555ddbb"
        "bdd55555ddb"
        "bdd55d55ddb"
        "bdd5d55dddb"
        "bdd5d55dddb"
        "bdd5dd35dddb"
        "bbdd5d5ddbbb"
        "bbbdd5ddbbbb"
        "bbbb555bbbbb"
    };
    draw_img(u,v,bolder);
    wait_us(250);
}
    