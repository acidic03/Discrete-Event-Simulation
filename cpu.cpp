//
// Created by Matthew Cohen on 9/8/19.
//

#include "cpu.h"

namespace mc
{
    Cpu::Cpu(std::priority_queue<mc::Globals::Event, std::vector<mc::Globals::Event>, mc::Globals::CompareEvents>* eventsPQ)
    {
        this->m_eventsPQ = eventsPQ;
    }

    void Cpu::handleArrival(mc::Globals::Event e)
    {
        // add event to queue
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

// TODO: redo function
    void Cpu::handleExit(mc::Globals::Event e, Disk* disk1, Disk* disk2)
    {
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d exits the CPU\n", e.time, e.pid);
        m_occupied = 0;
        // begin setup for temp event
        mc::Globals::Event tempEvent = {
                .pid = e.pid
        };

        if (((double)rand() / RAND_MAX) < mc::Globals::QUIT_PROB)
        {
            // exit event
            tempEvent.type = mc::Globals::PROCESS_EXIT_SYSTEM;
            tempEvent.time = mc::Globals::currentTime;
        }
        else
        {
            // use a disk
            if ((!disk1->isOccupied() && disk1->getQueue()->empty()) || (!disk2->isOccupied() && disk2->getQueue()->empty()))
            {
                // 50/50 chance to choose disk 1 or disk 2 if both are empty and not occupied

                if ( ((double)rand() / RAND_MAX) < 0.5)
                {
                    // disk 1
                    tempEvent.type = mc::Globals::DISK1_ARRIVAL;
                    tempEvent.time = e.time;
                }
                else
                {
                    // disk 2
                    tempEvent.type = mc::Globals::DISK2_ARRIVAL;
                    tempEvent.time = e.time;
                }

            }
            else if (disk1->getQueue()->size() < disk2->getQueue()->size())
            {
                tempEvent.type = mc::Globals::DISK1_ARRIVAL;
                tempEvent.time = e.time;
            }
            else
            {
                tempEvent.type = mc::Globals::DISK2_ARRIVAL;
                tempEvent.time = e.time;
            }
        }

        m_eventsPQ->push(tempEvent);

        // there are events in the CPU queue that need to be processed
        if (!m_queue.empty())
        {
            // remove event from cpu queue
            mc::Globals::Event temp = m_queue.front();
            m_queue.pop();

            // add event to priority queue for processing
            temp.type = mc::Globals::PROCESS_ARRIVE_CPU;
            m_occupied = 1;
            m_eventsPQ->push(temp);
        }

    }

    void Cpu::queueProcess(mc::Globals::Event e)
    {
        m_queue.push(e);
    }

    void Cpu::beginProcess(mc::Globals::Event e)
    {
        if (DEBUG_MESSAGES)
            printf("At time %d, process %d enters CPU\n", e.time, e.pid);
        m_occupied = 1;
        mc::Globals::Event newEvent = {
                .type = mc::Globals::PROCESS_FINISH_CPU,
                .time = mc::Globals::randomInt(mc::Globals::CPU_MIN, mc::Globals::CPU_MAX) + mc::Globals::currentTime,
                .pid = e.pid
        };
        m_eventsPQ->push(newEvent);
    }

    std::queue<mc::Globals::Event>* Cpu::getQueue() {
        return &m_queue;
    }

    int Cpu::isOccupied()
    {
        return m_occupied;
    }
}