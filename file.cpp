#include "file.h"

/*
    Takes the name of a config file as a parameter and
    defines the values for global use. File must be in
    a format that has one string followed by an integer 
    per line.
*/
int readConfigFile(std::string fileName)
{
    // is used to make sure all 12 required values are read, if not
    // view it as an error as there is a problem with the config file
    int valuesRead = 0;
    std::fstream configFile;
    configFile.open(fileName);

    if (configFile.good())
    {
        std::string name = "";
        int value;

        while (!configFile.eof())
        {
            configFile >> name;

            if (name == "SEED")
            {
                configFile >> value;
                VARS.SEED = value;
                printf("SEED value of %d\n", value);
                valuesRead++;
            }
            else if (name == "INIT_TIME")
            {
                configFile >> value;
                VARS.INIT_TIME = value;
                printf("INIT_TIME value of %d\n", value);
                valuesRead++;
            }
            else if (name == "FIN_TIME")
            {
                configFile >> value;
                VARS.FIN_TIME = value;
                printf("FIN_TIME value of %d\n", value);
                valuesRead++;
            }
            else if (name == "ARRIVE_MIN")
            {
                configFile >> value;
                VARS.ARRIVE_MIN = value;
                printf("ARRIVE_MIN value of %d\n", value);
                valuesRead++;
            }
            else if (name == "ARRIVE_MAX")
            {
                configFile >> value;
                VARS.ARRIVE_MAX = value;
                printf("ARRIVE_MAX value of %d\n", value);
                valuesRead++;
            }
            else if (name == "QUIT_PROB")
            {
                configFile >> value;
                VARS.QUIT_PROB = value;
                printf("QUIT_PROB value of %d\n", value);
                valuesRead++;
            }
            else if (name == "CPU_MIN")
            {
                configFile >> value;
                VARS.CPU_MIN = value;
                printf("CPU_MIN value of %d\n", value);
                valuesRead++;
            }
            else if (name == "CPU_MAX")
            {
                configFile >> value;
                VARS.CPU_MAX = value;
                printf("CPU_MAX value of %d\n", value);
                valuesRead++;
            }
            else if (name == "DISK1_MIN")
            {
                configFile >> value;
                VARS.DISK1_MIN = value;
                printf("DISK1_MIN value of %d\n", value);
                valuesRead++;
            }
            else if (name == "DISK1_MAX")
            {
                configFile >> value;
                VARS.DISK1_MAX = value;
                printf("DISK1_MAX value of %d\n", value);
                valuesRead++;
            }
            else if (name == "DISK2_MIN")
            {
                configFile >> value;
                VARS.DISK2_MIN = value;
                printf("DISK2_MIN value of %d\n", value);
                valuesRead++;
            }
            else if (name == "DISK2_MAX")
            {
                configFile >> value;
                VARS.DISK2_MAX = value;
                printf("DISK2_MAX value of %d\n", value);
                valuesRead++;
            }
            else
            {
                printf("unknow name/name in config file...\n");
                exit(1);
            }
            
        }
    }
    

    configFile.close();
    return valuesRead == REQUIRED_NUM_OF_VARS ? 1 : 0;
}