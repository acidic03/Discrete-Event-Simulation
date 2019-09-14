//
// Created by Matthew Cohen on 9/9/19.
//

#include "disk.h"

namespace mc
{
    Disk::Disk(std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* eventsPQ, DiskType disk)
    {
        this->m_eventsPQ = eventsPQ;
        this->m_diskType = disk;
    }

    void Disk::handleArrival(mc::Globals::Event e)
    {
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d begins I/O on Disk %d\n", e.time, e.pid, m_diskType);

        // currently working on a event or events are waiting to be processed
        if (m_occupied || !m_queue.empty())
        {
            queueProcess(e);
        }
        else if (!m_occupied && m_queue.empty())
        {
            // begin working on event now
            beginProcess(e);
        }
    }

    void Disk::queueProcess(mc::Globals::Event e)
    {
        m_queue.push(e);
    }

    void Disk::beginProcess(mc::Globals::Event e)
    {
        m_occupied = 1;
        mc::Globals::Event newEvent = {
                .pid = e.pid
        };

        switch (e.type)
        {
            case mc::Globals::DISK1_ARRIVAL:
                newEvent.type = mc::Globals::DISK1_FINISH;
                newEvent.time = mc::Globals::currentTime + mc::Globals::randomInt(mc::Globals::DISK1_MIN, mc::Globals::DISK1_MAX);
                break;
            case mc::Globals::DISK2_ARRIVAL:
                newEvent.type = mc::Globals::DISK2_FINISH;
                newEvent.time = mc::Globals::currentTime + mc::Globals::randomInt(mc::Globals::DISK2_MIN, mc::Globals::DISK2_MAX);
                break;
            default:
                break;
        }
        m_eventsPQ->push(newEvent);
    }

    void Disk::handleExit(mc::Globals::Event e)
    {
        // TODO: determine the quit probability or send back to cpu
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d finishes I/O on Disk %d\n", e.time, e.pid, m_diskType);
        m_occupied = 0;

        // check for waiting events in the queue
        if (!m_queue.empty())
        {
            mc::Globals::Event temp = m_queue.front();
            // need to check which disk the event belongs to
            switch (m_diskType)
            {
                case DiskType::DISK_1:
                    temp.type = mc::Globals::DISK1_ARRIVAL;
                    break;
                case DiskType::DISK_2:
                    temp.type = mc::Globals::DISK2_ARRIVAL;
                    break;
            }
            m_occupied = 1;
            m_eventsPQ->push(temp);
        }
    }

    int Disk::isOccupied()
    {
        return m_occupied;
    }

    std::queue<mc::Globals::Event>* Disk::getQueue()
    {
        return &m_queue;
    }
}