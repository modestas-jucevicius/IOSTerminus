#include "terminuslib.h"

#define NKEYS (sizeof(lookuptable)/sizeof(t_mapfunc))

/////////////////////////////////////// Global variables

int game_state;

dir_t gameDirs[NUMDIR];

/////////////////////////////////////// Event functions

/**
 * 
 */
int big_orc(int argc, char* argv[]){
    if(strcmp("Big_hole", argv[2])==0){
        printf("Now the orc is stuck");
    } else {
        printf("Oh no!, the orc has escaped!");
        game_state = S_END;
    }
    return game_state;
}

/**
 * 
 */
int boulder(int argc, char* argv[]){
    return game_state;
}

/**
 * 
 */
int planks(int argc, char* argv[]){
    if(strcmp("Small_lake", argv[2])==0){
        printf("I could use these to repair the boat!");
    }
    return game_state;
}
/////////////////////////////////////// Main executable

static t_mapfunc lookuptable[] = {
    { "big_orc", big_orc }
};

t_func_event keyfromstring(char *key)
{
    int i;
    for (i=0; (long unsigned int) i < NKEYS; i++) {
        t_mapfunc *map = &(lookuptable[i]);
        if (strcmp(map->key, key) == 0)
            return map->ev;
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int nArgFifo;
    fifo_read(&nArgFifo, &game_state, gameDirs);

    t_func_event func = keyfromstring(argv[1]);
    int result = func(argc, argv);

    exit(result);
}
