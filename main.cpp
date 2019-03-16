// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file

/*Changes 1.0
- added new next_map() function
- portal relocation
- set active_map to 1 in portal
- Added new pushuttons to the list


*/
/* To create a new Map
- try changing everything to default
- 
*/
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void next_map();
int main ();
int startScreen(GameInputs game, int start);
int changeCharacter(GameInputs game);
void displayDragon();


// Game parameters
int counter = 6;
int seen_master = 0;
int health = 100;
int omni = 0; // omnipotent mode to enable walking through walls
int chooseChar = 0; 
int state = 0;
int lives = 3;
int active_map; //Switching between maps
int menu = 0;
int chocCounter = 0; // Chocolates levels up the characters
int k =0;
int read = 0;


/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key; //if player has key
} Player;



/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define ACTION_BUTTON2 7
#define ACTION_BUTTON3 8

/**
get_action() uses accelerometer readings to move the position
of the character. It also takes in pushbutton inputs to toggle between 
menu options or choose characters.
*/

int get_action(GameInputs inputs)
    
{
    if (inputs.ax < -0.2){
        if ((inputs.ax*inputs.ax) > (inputs.ay*inputs.ay)) {
            return GO_RIGHT;
        } else {
            return GO_UP;
        }
    
    } else if (inputs.ax  > 0.2){
        if ((inputs.ax*inputs.ax)  >(inputs.ay*inputs.ay)) {
            return GO_LEFT;
        } else {
            return GO_DOWN;
        }
    
    } else if (inputs.ay > 0.2){
        if ((inputs.ay*inputs.ay) > (inputs.ax*inputs.ax)) {
            return GO_UP;
        } else {
            return GO_RIGHT;
        }
    
    } else if (inputs.ay < -0.2){
        if ((inputs.ay*inputs.ay) > (inputs.ax*inputs.ax)) {
            return GO_DOWN;
        } else {
            return GO_LEFT;
        }
    
    } else if (inputs.b1 == 0) { 
        wait(.2); //Debounce
        return ACTION_BUTTON;
    
    } else if (inputs.b2 == 0) {
        wait(.2); //Debounce
        return ACTION_BUTTON2;
    
    } else if (inputs.b3 == 0) {
        wait(.2); //Debounce
        return MENU_BUTTON;
    
    } else {
     return NO_ACTION;
    }
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
 
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
#define ORANGE      0xFFA500 //orange
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    MapItem* map;
    GameInputs game;

    uLCD.locate(0,0);
    uLCD.textbackground_color(BURGUNDY);
    uLCD.printf("(%d, %d)" ,Player.x, Player.y);
    
    
    // If player dies but still has lives left, player can respawn
    if (health == 0 && lives > 0) {
        uLCD.cls();
        uLCD.locate(5,5);
        uLCD.textbackground_color(BLUE);
        uLCD.background_color(BLUE);
        uLCD.printf("You died!");
        uLCD.locate(4,8);
        lives--;
        uLCD.printf("lives left: %d", lives);
        wait(3.00);
        health = 100;
        draw_lower_status();
        draw_upper_back(health);
        draw_game(1);
    }
    // if player loses all their lives, he can no longer continue playing
    else if (health == 0 && lives == 0) {
        uLCD.cls();
        uLCD.textbackground_color(BLUE);
        uLCD.background_color(BLUE);
        while (1) {
        uLCD.locate(5,5);
        uLCD.printf("Sorry!");
        uLCD.locate(3,7);
        uLCD.printf("You Lost!");
        }
    }
    // If the player picks up multiple chocaltes, they level up
    if (chocCounter == 4) {
        chooseChar = 3;
    }
    //Switch to a different map if player reaches these coordinates
    if (Player.x == 40 && Player.y == 40 && active_map == 0) {
            active_map = 1;
            next_map();
            Player.x = 7;
            Player.y = 7;
            draw_game(1); 
            return FULL_DRAW;  
        }
    
    /*
    Switch case statements for players to go in either direction, If there
    is a wall, player cannot move unless omnipotent mode is enabled. Player can 
    interact with the following objects:
    1. Master: master gives a mission for the player to collect dragonballs and 
    return them back to him
    2. Chocolate: Player can increase thier chocolate counter by walking over them
    3. Fire: Player loses health by walking on fire. walking over fire several times
    can cause the player to lose their lives.
    4. Portal: The portal takes the player into different dimension (different map) 
    */
    
    switch(action)
    {
        case GO_UP:
        map = get_north(Player.x, Player.y);
        if (map->walkable || omni) {
            Player.py = Player.y;
            Player.y--;
        }
        if (map->type == 7) {
            speaker.period(1.0/250.0); // 500hz period
            speaker =0.5; //50% duty cycle - max volume
            wait(0.3);
            speaker=0.0; // turn off audio
            health-=50;
            uLCD.locate(5,5);
            uLCD.textbackground_color(BLACK);
            uLCD.printf("OUCH!");
            draw_upper_back(health);
            draw_game(1);
        } if (map->type == 5) {
            chocCounter++;
        }
        break;    
        
        case GO_LEFT:
        map = get_west(Player.x, Player.y);
        if (map->walkable || omni) {
            Player.px = Player.x;
            Player.x--;
        }
        if (map->type == 7) {
            speaker.period(1.0/250.0); // 500hz period
            speaker =0.5; //50% duty cycle - max volume
            wait(0.3);
            speaker=0.0; // turn off audio
            health-=50;
            uLCD.locate(5,5);
            uLCD.textbackground_color(BLACK);
            uLCD.printf("OUCH!");
            draw_upper_back(health);
            draw_game(1);
        }  if (map->type == 5) {
            chocCounter++;
        } 
        break;            
        case GO_DOWN:
        map = get_south(Player.x, Player.y);
        if (map->walkable || omni) {
            Player.py = Player.y;
            Player.y++;
        }
        if (map->type == 7) {
            speaker.period(1.0/250.0); // 500hz period
            speaker =0.5; //50% duty cycle - max volume
            wait(0.3);
            speaker=0.0; // turn off audio
            health-=50;
            uLCD.locate(5,5);
            uLCD.textbackground_color(BLACK);
            uLCD.printf("OUCH!");
            draw_upper_back(health);
            draw_game(1);
        } if (map->type == 9) {
            map_erase(13,43);
            draw_bolder(13,43);
            
        }  if (map->type == 5) {
            chocCounter++;
        }
        break;
        case GO_RIGHT:
        map = get_east(Player.x, Player.y);
        
        if (map->walkable || omni) {
            Player.px = Player.x;
            Player.x++;
        }
        map = get_here(Player.x, Player.y);  
        if (map->type == 7) {
            speaker.period(1.0/250.0); // 500hz period
            speaker =0.5; //50% duty cycle - max volume
            wait(0.3);
            speaker=0.0; // turn off audio
            health-=50;
            uLCD.locate(5,5);
            uLCD.textbackground_color(BLACK);
            uLCD.printf("OUCH!");
            draw_upper_back(health);
            draw_game(1);;
        }  if (map->type == 5) {
            chocCounter++;
        }
        break;
        case ACTION_BUTTON: 
            if (counter <= 0 && game.b1 == 0 && ((Player.x ==7 && Player.y == 13) || (Player.x ==9 && Player.y == 13) || (Player.x ==8 && Player.y == 12) || (Player.x ==8 && Player.y == 14))) {
                uLCD.textbackground_color(ORANGE);
                uLCD.color(LGREY);
                map_erase(9, 13);
                add_player_side(9,13);
                speech("Congrats!!!", "");
                speech("You are worthy", "");
                speech("You are", "Super Sayin");
                 map_erase(9,13);
                draw_game(1);
                add_door(46,46);
                seen_master = 1;
            } else if (game.b1 == 0 && ((Player.x ==7 && Player.y == 13) || (Player.x ==9 && Player.y == 13) || (Player.x ==8 && Player.y == 12) || (Player.x ==8 && Player.y == 14))) 
            {
                draw_lower_back(7, chocCounter);
                uLCD.textbackground_color(ORANGE);
                uLCD.color(LGREY);
                map_erase(9, 13);
                add_player_side(9,13);
                speech("Hello there!", "");
                speech("I am Master Chief","");
                speech("You are the ","chosen one");
                speech("To complete ","the mission");
                speech("Collect the", "DragonBalls");
                speech("and bring them", "back to me");
                map_erase(9,13);
                //add_player(9, 13);
                draw_game(1);
                displayDragon();
                draw_lower_back(6, chocCounter);
                wait_us(250);
            } else if (game.b1 == 0) {
                omni++;
                omni = omni % 2;
                if (omni) {
                uLCD.textbackground_color(ORANGE);
                speech("SUPER SAYIN", "MODE!!!");
                draw_game(1);
                } else {
                speech("Normal","");
                draw_game(1);
                }                
            }     
        break;
        case ACTION_BUTTON2:
            
            if (counter > 0 && game.b2 == 0 && ((Player.x ==45 && Player.y == 9) || (Player.x ==25 && Player.y == 32) || (Player.x ==31 && Player.y == 15))) {
                counter--;
                
                draw_lower_back(counter, chocCounter);    
            } if (counter > 0 && game.b2 == 0 && ((Player.x ==5 && Player.y == 42) || (Player.x ==47 && Player.y == 43) || (Player.x ==12 && Player.y == 27))) {
                counter--;
                draw_lower_back(counter, chocCounter);
            } if (seen_master && game.b2 == 0 && (Player.x == 46 && Player.y == 46)) {
                uLCD.filled_rectangle(0,0,127,127,RED);
                wait(0.2);
                uLCD.filled_rectangle(0,0,127,127,BLUE);
                wait(0.2);
                uLCD.filled_rectangle(0,0,127,127,GREEN);
                wait(0.2);
                uLCD.filled_rectangle(0,0,127,127,ORANGE);
                wait(0.2);
                uLCD.locate(5,7);
                uLCD.color(RED);
                uLCD.printf("GAME OVER");
                uLCD.locate(3,8);
                uLCD.printf("Congrats!!!!");
                uLCD.locate(3,9);
                uLCD.printf("YOU WON!!!");
                wait(10.0);
                return GAME_OVER;
            } 

        default:        
        break;
    }

    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    //int OverDrawn;
    // Draw game border first

    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if ((i == 0 && j == 0)) {// Only draw the player on init
   
                 if (chooseChar == 0) {
                    draw_player(u, v, Player.has_key);
                    }
                else if (chooseChar == 1) {
                    draw_img(u, v, masterSprite);
                }
                else if (chooseChar == 2 ) {
                    draw_img(u, v, image);
                }
                else if (chooseChar == 3) {
                    draw_player2(u, v, Player.has_key);
                }
                    else {draw_img(u,v,image);}

                continue;
            }
             // Current (i,j) in the map
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height())
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                 // Only draw if they're different
                if (init || curr_item != prev_item)
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                
            }
             // Current (i,j) in the map
             else if (x >= 0 && y >= 0 && x < map_width() && y < map_height())
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
             // If doing a full draw, but we're out of bounds, draw the walls.
            else if (init)
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    draw_upper_back(health);
    draw_lower_back(counter, chocCounter); 
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    active_map = 0;
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    add_master(8,13);
    add_portal(40,40);
    
    //Add items at specified places
    for (int i = 0; i < 5; i++) {
        
        add_wall(12,i+43,VERTICAL, map_height());
        add_wall(i+14,43,HORIZONTAL, map_width());
        add_wall(19,i+43, VERTICAL, map_height());
        }
       
        add_bolder(13,43);
    
    for (int i = 0; i < 12; i+=5)
    {
        add_chocolate(i+6,i+3);
    }
    
    
    for (int i = 0; i < 12; i+=4)
    {
        add_fire(i+ 9, i + 4);
    }
    print_map();
    add_portal(18,45);
}

// Initializing a different dimension
void next_map()
{
    uLCD.cls();
    active_map = 1;
    Map* map2 = set_active_map(1);
    add_wall(0, 0,HORIZONTAL, map_width());

}


/**
    The game initalizes with a start screen where the player has
    the option whether to start game or switch characters. The markers are
    indicated with a red arrow and toggles and selectes the options using
    pushbuttons
*/
int StartScreen(GameInputs game) { //int start) {

    uLCD.locate(2,2);
    uLCD.color(BLUE);

    uLCD.printf("Quest Explorer");
    uLCD.locate(4,4);

    uLCD.color(GREEN);
    uLCD.printf("Start game");
    
    uLCD.locate(4,6);
    uLCD.printf("Change");
    uLCD.locate(4,7);
    uLCD.printf("Character");
    

    
    if (game.b2 ==0) {

        uLCD.line(17,35,7,35,BLACK);
        uLCD.line(17,35,14,32,BLACK);
        uLCD.line(17,35,14,38,BLACK);
        uLCD.line(17,48,7,48,RED);
        uLCD.line(17,48,14,45,RED);
        uLCD.line(17,48,14,51,RED);
        state = 1;
    }
    if (game.b3 == 0) {
        uLCD.line(17,48,7,48,BLACK);
        uLCD.line(17,48,14,45,BLACK);
        uLCD.line(17,48,14,51,BLACK);
        uLCD.line(17,35,7,35,RED);
        uLCD.line(17,35,14,32,RED);
        uLCD.line(17,35,14,38,RED);
        state = 0;
       }
    
    if (game.b1 == 0) {
        
  
        for (k=0; k<=800; k=k+100) {
        speaker.period(1.0/float(k));
        speaker=0.25;
        wait(.1);
        if (k == 800) {
            speaker.period(0);
            break;
        }
    }
    wait(2);
 
        return 0;
    } 
    return 1;  
}

/*
  If the player selects Change character item on the start screen,
  this function runs which allows the player to 
  toggle between multiple characters
*/
int changeCharacter(GameInputs in) {
    draw_player(50, 25, 0);
    draw_master(50,50);
    draw_player2(50, 75, 0);
    draw_img(50,100, image);
    if (in.b1 == 0){
        chooseChar = 0;
        return 0;
    }
    if (in.b2 == 0){
        chooseChar = 1;
        return 0;
    }
    if (in.b3 == 0) {
        chooseChar = 2;
        return 0;
    }
    if (in.b4 == 0) {
        chooseChar = 3;
        return 0;
    } 
    return 1;
}


/**
  Adds dragon balls in specified locations
 */
 void displayDragon() {

    add_dragon_ball1(45,9);
    add_dragon_ball2(25,32);
    add_dragon_ball3(31,15);
    add_dragon_ball4(5,42);
    add_dragon_ball5(47,43);
    add_dragon_ball6(12,27);

}
int main()
{
    uLCD.line(17,35,7,35,RED);
    uLCD.line(17,35,14,32,RED);
    uLCD.line(17,35,14,38,RED);
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    
    //Intializations in main
    int action2 = 1;
    GameInputs inputs;
    
    //Run startScreen until player selects any option
    while (action2) {
        inputs = read_inputs();
        action2 = StartScreen(inputs);
        
    }
     uLCD.cls();
    action2 = 1;
    // Choose character
    while (action2 && state) {
        inputs = read_inputs();
        action2 = changeCharacter(inputs);
    }
    
    

    // Initialize the maps
    maps_init();
    init_main_map(); 
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;

    // Initial drawing
    draw_game(true);
    
    
    // Main game loop
    int action1 = 0;
    GameInputs inputss;
    
    /**
    Run the game. The following sequence of events occur
         1. Read inputs        
         2. Determine action (get_action)        
         3. Update game (update_game)
         3b. Check for game over
         4. Draw frame (draw_game)       
         5. Frame delay
    */
    while(1)
    {
        // Timer to measure game update speed
        Timer t; 
        t.start();
        inputss = read_inputs();
        int action = get_action(inputss);
        action1 = update_game(action);
        //if (action1 != 1) {
        //inputs = read_inputs();
        draw_game(action1);
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}
