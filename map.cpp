#include "map.h"
#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map map2;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    int num = 0.5 * (X+Y) * (X+Y+1) + Y;
    return num;

}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key % 4;
}
void maps_init()
{
    if (active_map == 0) {
    map.items = createHashTable(map_hash, 4);
    map.h = MAP_HEIGHT;
    map.w = MAP_WIDTH;
    }
    if (active_map == 1) {
    map2.items = createHashTable(map_hash, 4);
    map2.h = MAP_HEIGHT;
    map2.w = MAP_WIDTH;
    }
}

Map* get_active_map()
{
    // There's only one map
    if (active_map == 0){
        return &map;
    } else if (active_map == 1) {
        return &map2;
    }
}

Map* set_active_map(int m)
{
    active_map = m;
    if (active_map == 0){
        return &map;
    } else if (active_map == 1) {
        return &map2;
    }
}
//Prints map
void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P','M', 'C'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}
// Prints map for another dimension
void print_map1() 
{   
    char lookup[] = {'W'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
   return MAP_WIDTH; 
}

int map_height()
{
    return MAP_HEIGHT;
}

int map_area()
{
    return MAP_WIDTH * MAP_HEIGHT;
}

MapItem* get_north(int x, int y)
{
    if (active_map == 0) {
    int key = XY_KEY(x,y-1);
    //int key = map_hash(num);
    return (MapItem*)getItem(map.items, key); 
    } else if (active_map == 1) {
        int key = XY_KEY(x,y-1);
        return (MapItem*)getItem(map2.items, key); 
    }
}

MapItem* get_south(int x, int y)
{
    if (active_map == 0) {
    int key = XY_KEY(x,y+1);
    //int key = map_hash(num);
    return (MapItem*)getItem(map.items, key); 
    } else if (active_map == 1) {
        int key = XY_KEY(x,y+1);
        return (MapItem*)getItem(map2.items, key); 
    }
}

MapItem* get_east(int x, int y)
{
      if (active_map == 0) {
    int key = XY_KEY(x+1,y);
    //int key = map_hash(num);
    return (MapItem*)getItem(map.items, key); 
    } else if (active_map == 1) {
        int key = XY_KEY(x+1,y);
        return (MapItem*)getItem(map2.items, key); 
    }
}

MapItem* get_west(int x, int y)
{
    if (active_map == 0) {
    int key = XY_KEY(x-1,y);
    //int key = map_hash(num);
    return (MapItem*)getItem(map.items, key); 
    } else if (active_map == 1) {
        int key = XY_KEY(x-1,y);
        return (MapItem*)getItem(map2.items, key); 
    }
}

MapItem* get_here(int x, int y)
{
    if (active_map == 0) {
    int key = XY_KEY(x,y);
    //int key = map_hash(num);
    return (MapItem*)getItem(map.items, key);
    } else if (active_map == 1) {
    int key = XY_KEY(x,y);
    //int key = map_hash(num);
    return (MapItem*)getItem(map2.items, key);
    }

}


void map_erase(int x, int y)
{
if (active_map == 0) {

    int key = XY_KEY(x,y);
    removeItem(map.items,key);
    } else if (active_map == 1) {

    int key = XY_KEY(x,y);
    removeItem(map2.items,key);
    }

}


//Parameters for different objects in the map

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_master(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = MASTER;
    w1-> draw = draw_master;
    w1-> walkable = false;
    w1-> data = NULL;
    void* vals = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (vals) free(vals); // If something is already there, free it
}
void add_chocolate(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = CHOCOLATE;
    w1-> draw = draw_chocolate;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball1(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball1;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball2;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball3(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball3;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball4(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball4;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball5(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball5;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_dragon_ball6(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = KEY;
    w1-> draw = draw_dragonball6;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_door(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = DOOR;
    w1-> draw = draw_door;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_fire(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = FIRE;
    w1-> draw = draw_fire;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_portal(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = PORTAL;
    w1-> draw = draw_portal;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_bolder(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = BODLER;
    w1-> draw = draw_bolder;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_player_side(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1-> type = BODLER;
    w1-> draw = draw_player_side;
    w1-> walkable = true;
    w1-> data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}