#include "speech.h"

#include "globals.h"
#include "hardware.h"

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 127, 127, 106, RED);
    uLCD.filled_rectangle(2, 125, 125, 108, ORANGE);
}

void erase_speech_bubble()
{
   uLCD.filled_rectangle(0, 127, 127, 108, BLACK);
    
}

void draw_speech_line(const char* line, int which)
{
    uLCD.color(BLACK);
    uLCD.set_font_size(1,1);
    uLCD.locate(1 , 14 + which);
    uLCD.puts((char*)line);
}

void speech_bubble_wait()
{
    wait(2.00);
}
// Speech bubles displayed on the bottom
void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    uLCD.color(WHITE);
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    speech_bubble_wait();
    erase_speech_bubble();
}


