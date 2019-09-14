# Discrete Event Simulator
Matthew Cohen - Lab 1

The purpose of this project is to simulate how processes move through a computing system using a scheduler. The program parses a required config file to load the associated values to use in the simulation.

The program simulates a CPU scheduler by storing process/events by using queues as the data structure. A priority queue is used to hold the events before the are sent to a device according to their event type. The priority queue is sorted by the lowest time to ensure each event gets processed accordingly. The CPU and both disks also have their own FIFO queues to hold events when the current device is busy and to be worked on when free. The event simulation can be summed up by looking at the illustration below to understand the proper flow of the program.

### insert picture of illustration here
