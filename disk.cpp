//
// Created by Matthew Cohen on 9/9/19.
//

#include "disk.h"

namespace mc
{
    Disk::Disk(std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* eventsPQ, DiskType disk, std::ofstream &outputFile) : m_outputFile(outputFile)
    {
        this->m_eventsPQ = eventsPQ;
        this->m_diskType = disk;

    }

    void Disk::handleArrival(mc::Globals::Event e)
    {
        if (CREATE_LOG_FILE)
            m_outputFile << e.time << "," << e.pid << ",Begin Disk " << m_diskType << " I/O\n";
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d begins I/O on Disk %d\n", e.time, e.pid, m_diskType);

        // currently working on a event or events are waiting to be processed
        // add event to queue
        if (!m_occupied && m_queue.empty())
        {
            beginProcess(e);
        }
        else
        {
            queueProcess(e);
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
            case mc::Globals::PROCESS_ARRIVE_DISK1:
                newEvent.type = mc::Globals::PROCESS_FINISH_DISK1;
                newEvent.time = mc::Globals::currentTime + mc::Globals::randomInt(mc::Globals::DISK1_MIN, mc::Globals::DISK1_MAX);
                break;
            case mc::Globals::PROCESS_ARRIVE_DISK2:
                newEvent.type = mc::Globals::PROCESS_FINISH_DISK2;
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
        if (CREATE_LOG_FILE)
            m_outputFile << e.time << "," << e.pid << ",Finish Disk " << m_diskType << " I/O\n";
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d finishes I/O on Disk %d\n", e.time, e.pid, m_diskType);

        // check for waiting events in the queue
        if (!m_queue.empty())
        {
            mc::Globals::Event temp = m_queue.front();
            m_queue.pop();
            beginProcess(temp);
        }
        else
        {
            m_occupied = 0;
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