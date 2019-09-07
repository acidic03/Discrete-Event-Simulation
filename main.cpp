/*
    - Read values from the config file
    - Store events in a priority queue and loop until I reach
    the simulation finished event
    -
*/

#include <queue>
#include "file.h"



int main()
{
    // read values from config file and only continue if the file was
    // read successfully
    if (readConfigFile("config1.txt"))
    {
        printf("success..\n");
        // main priority queue to store the events


    }

    return 0;
}
