//
// Created by Matthew Cohen on 9/8/19.
//

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <queue>

#include "globals.h"
#include "disk.h"

namespace mc
{
    class Cpu {
    private:
        std::queue<mc::Globals::Event> m_queue;
        std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* m_eventsPQ;
        int m_occupied;

        // adds a Event to the queue when the cpu is busy
        void queueProcess(mc::Globals::Event e);
        // begins working on a Event when the cpu is free
        void beginProcess(mc::Globals::Event e);
    public:
        Cpu(std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* eventsPQ);
        void handleArrival(mc::Globals::Event e);
        void handleExit(mc::Globals::Event e, mc::Disk* disk1, mc::Disk* disk2);
        int isOccupied();

        std::queue<mc::Globals::Event>* getQueue(void);
    };
}

#endif //CPU_H
