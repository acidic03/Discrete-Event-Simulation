//
// Created by Matthew Cohen on 9/9/19.
//

#ifndef DISK_H
#define DISK_H

#include <queue>

#include "globals.h"

namespace mc
{
    enum DiskType {
        DISK_1,
        DISK_2
    };

    class Disk {
    protected:
        std::queue<mc::Globals::Event> m_queue;
        std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* m_eventsPQ;
        int m_totalUseTime;
        // is used to tell which disk is which when there are multiple
        DiskType m_diskType;
        int m_occupied;

        // adds a Event to the queue when the cpu is busy
        void queueProcess(mc::Globals::Event e);
        // begins working on a Event when the cpu is free
        void beginProcess(mc::Globals::Event e);

    public:
        Disk(std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* eventsPQ, DiskType disk);
        void handleArrival(mc::Globals::Event e);
        void handleExit(mc::Globals::Event e);
        int isOccupied();
        std::queue<mc::Globals::Event>* getQueue();
    };
}



#endif //DISK_H
