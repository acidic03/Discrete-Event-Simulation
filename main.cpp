// TODO: write to a log file
//      Time the event
//      Process ID
//      Description of the event
// TODO: Create a STAT file
//      Each queue average and maximum size
//      Utilization - how much time a component was used divided by the total amount of simulation time
//      Average and maximum response time
//      Throughput of each component
// TODO: Create documentation
//      High level overview of program
//      Brief explanation
//      Create Github markdown readme


#include <queue>
#include <stdlib.h>

#include "file.h"
#include "cpu.h"
#include "disk.h"


// Functions
void initSimulation(void);
void handleEvent(mc::Globals::Event e);
void processArrival(mc::Globals::Event e);

// main priority queue to store the events
std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents> eventsPQ;


mc::Cpu cpu(&eventsPQ);
mc::Disk disk1(&eventsPQ, mc::DiskType::DISK_1);
mc::Disk disk2(&eventsPQ, mc::DiskType::DISK_2);


int m_simFinished = 0;

int main()
{
    // read values from config file and only continue if the file was
    if (mc::readConfigFile("config.txt"))
    {
        // read successfully continue with setup
        initSimulation();
        // use the SEED provided for random numbers
        srand(mc::Globals::SEED);


        // loop until priority queue is empty
        while (!m_simFinished) {
            // set the current time to the time of the event removed
            mc::Globals::Event temp = eventsPQ.top();
            mc::Globals::currentTime = temp.time;
            eventsPQ.pop();
            handleEvent(temp);
        }
    }

    return 0;
}

void initSimulation()
{
    mc::Globals::Event arrivalEvent = {
            .time = 0,
            .pid = ++mc::Globals::pidCounter,
            .type = mc::Globals::PROCESS_ARRIVAL
    };

    mc::Globals::Event finishedEvent = {
            .time = mc::Globals::FIN_TIME,
            .pid = ++mc::Globals::pidCounter,
            .type = mc::Globals::SIMULATION_FINISHED
    };

    eventsPQ.push(arrivalEvent);
    eventsPQ.push(finishedEvent);
}

void handleEvent(mc::Globals::Event e) {

    switch (e.type) {
        case mc::Globals::PROCESS_ARRIVAL:
            processArrival(e);
            break;
        case mc::Globals::PROCESS_ARRIVE_CPU:
            cpu.handleArrival(e);
            break;
        case mc::Globals::PROCESS_FINISH_CPU:
            cpu.handleExit(e, &disk1, &disk2);
        case mc::Globals::PROCESS_EXIT_SYSTEM:
            if (DEBUG_MESSAGES)
                printf("At time %d, process %d exits the system\n", e.time, e.pid);
            break;
        case mc::Globals::DISK1_ARRIVAL:
            disk1.handleArrival(e);
            break;
        case mc::Globals::DISK2_ARRIVAL:
            disk2.handleArrival(e);
            break;
        case mc::Globals::DISK1_FINISH:
            disk1.handleExit(e);
            break;
        case mc::Globals::DISK2_FINISH:
            disk2.handleExit(e);
            break;
        case mc::Globals::SIMULATION_FINISHED:
            m_simFinished = 1;
            break;
        default:
            break;
    }

}

void processArrival(mc::Globals::Event e)
{
    if (DEBUG_MESSAGES)
        printf("At time %d, process %d enters system\n", e.time, e.pid);
    mc::Globals::Event newEvent = {
            .time = mc::Globals::currentTime,
            .type = mc::Globals::PROCESS_ARRIVE_CPU,
            .pid = e.pid
    };
    eventsPQ.push(newEvent);

    // keep adding new events
    int newTime = mc::Globals::randomInt(mc::Globals::ARRIVE_MIN, mc::Globals::ARRIVE_MAX) + mc::Globals::currentTime;

    mc::Globals::Event temp = {
            .type = mc::Globals::PROCESS_ARRIVAL,
            .time = newTime,
            .pid = ++mc::Globals::pidCounter
    };
    eventsPQ.push(temp);
}