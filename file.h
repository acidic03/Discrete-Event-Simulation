#ifndef FILE_H
#define FILE_H

#define REQUIRED_NUM_OF_VARS 12

#include <string>
#include <fstream>

/*
    Is used to hold all of the values needed for use 
    for the program to run.
*/
struct
{
    int SEED;
    int INIT_TIME;
    int FIN_TIME;
    int ARRIVE_MIN;
    int ARRIVE_MAX;
    int QUIT_PROB;
    int CPU_MIN;
    int CPU_MAX;
    int DISK1_MIN;
    int DISK1_MAX;
    int DISK2_MIN;
    int DISK2_MAX;
} VARS;

/**
 * Read values from a text file and stores them in the VARS struct for later use
 * @param fileName The name of the config to load
 * @return 1 if all REQUIRED_NUM_OF_VARS are loaded, 0 if file is formatted incorrectly
*/
int readConfigFile(std::string fileName);

#endif