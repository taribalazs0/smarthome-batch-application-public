## Smart Home Control System

This project is an object-oriented smart home simulation framework written in C++. The program allows for the centralized management, status querying, and modification of various smart devices (lights, locks, thermostats).

## Architecture and Class Hierarchy

The project is built on the principles of polymorphism. The central controller stores the devices in a heterogeneous collection.

Device: Abstract base class. Defines the core interface for all devices (printStatus, update, save, getID).

Light: Smart light. It has a BRIGHTNESS parameter, with values ranging from 0 to 100(%).

Lock: Smart door lock. It has two states (STATE): 0 (unlocked/inactive) and 1 (locked/active).

Thermo: Smart thermostat. It regulates the temperature (TEMPERATURE) between 15°C and 35°C.

SmartHome: The central controller class. It stores the registered devices in a dynamically managed std::vector containing Device* pointers (heterogeneous collection). It is responsible for processing commands and managing memory.

## Features and Commands (Batch Processing)

The system supports batch command processing from a standard input stream or a file via the runBatch(std::istream& is) function.

Supported commands and syntax:

1. Add a Device (ADD)

Registers a new device in the system. If the identifier (ID) already exists, the system throws a DuplicateIDException.

Format: ADD <TYPE> <ID> <INITIAL_VALUE>

Examples:

ADD LAMP L01 80 (A light with ID 'L01' at 80% brightness)

ADD LOCK FrontDoor 1 (A lock with ID 'FrontDoor' in a locked state)

ADD THERMO LivingRoom 22.5 (A thermostat with ID 'LivingRoom' set to 22.5 degrees)

2. Update a Parameter (SET)

Updates a specific parameter of an already existing device.

Format: SET <ID> <PARAMETER> <NEW_VALUE>

Examples:

SET L01 BRIGHTNESS 50

SET FrontDoor STATE 0

SET LivingRoom TEMPERATURE 24

3. List States (LIST)

Prints the current status of all registered devices in the system to the provided output stream (e.g., console).

Format: LIST

4. Delete a Device (DEL)

Removes a device from the system (and properly frees the allocated memory).

Format: DEL <ID>

Example: DEL L01

5. Save System State (SAVE)

Saves the entire current system state to a text file in a format (exclusively as a sequence of ADD commands) that allows the system to be fully restored later.

Format: SAVE <FILENAME>

Example: SAVE config.txt

## Exception Handling

The program features robust exception handling, defined in exception.h:

SmartHomeException: Base class for basic errors (inherits from std::runtime_error).

InvalidParameterException: Thrown when an invalid parameter name is provided or if a value falls out of the allowed range (e.g., setting light brightness to 150%).

DuplicateIDException: Thrown when an ADD command attempts to use an ID that already exists in the collection.

## Testing and Memory Leak Detection

The project includes external (educational) tools to ensure code quality:

memtrace.h (Memory Leak Detector): Using macros, it automatically tracks new and delete calls. It alerts you upon program termination if any memory was left unfreed (e.g., if the SmartHome destructor failed to delete the vector elements).

gtest_lite.h: A lightweight framework similar to Google Test for writing unit tests (TEST, EXPECT_EQ, EXPECT_THROW, etc.).

## Compilation and Execution

Since the project uses standard C++ code, it can be compiled with any modern C++ compiler (GCC, Clang, MSVC). It is recommended to use C++11 or a newer standard.

Console compilation (example using GCC):

g++ -std=c++11 -Wall -DMEMTRACE -o smarthome main.cpp light.cpp lock.cpp thermo.cpp smarthome.cpp
./smarthome


(Note: The -DMEMTRACE flag enables the memory leak detector. A main.cpp and the implementation files are required for compilation.)
