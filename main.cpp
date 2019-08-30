/*
    - Read values from the config file
    - Store events in a priority queue and loop untill I reach
    the simulation finished event
    -
*/

#include <queue>
#include "file.h"



int main()
{
    // read values from config file and only continue if the file was
    // read successfully
    if (readConfigFile("config.txt"))
    {
        printf("success..\n");
        printf("SEED = %d\n", VARS.SEED);
    }
    else
    {
        printf("failure..\n");
    }
    
    // main priority queue to store the events
    

    return 0;
}
