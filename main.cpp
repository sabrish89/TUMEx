#include "Vehicle.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main()
{
    /* ####################
    INIT BLOCK 
    #################### */
    
    srand (static_cast <unsigned> (time(NULL))); // Master seed
    // Taxis
    vector<taxi> taxis;
    int taxi_count = 3;
    for (int i = 0; i < taxi_count; i++)
    {
        taxis.push_back(taxi(100, rand()%100)); // Assign random creation seed
        taxis[i].track();
    }
    // Buses
    vector<bus> buses;
    int bus_count = 5;
    for (int i = 0; i < bus_count; i++)
    {
        buses.push_back(bus(100, rand()%100)); // Assign random creation seed
        buses[i].track();
    }

    /* ####################
    SIMULATION LOOP 
    #################### */
    
    while (true)
    {   
        // Taxis
        int done_taxis = 0;
        if (taxi_count > done_taxis)
        {
            for (int i = 0; i < taxi_count; i++)
            {
                if (taxis[i].getState() > 5)
                {
                    done_taxis++;
                }
                else
                {
                    taxis[i].move();
                }
            }
        }
        // Buses
        int done_buses = 0;
        if (bus_count > done_buses)
        {
            for (int i = 0; i < bus_count; i++)
            {
                if (buses[i].bounded() != true)
                {
                    done_buses++;
                }
                else
                {
                    buses[i].move();
                }
            }
        }
        // SIM breaker
        if ( ( taxi_count == done_taxis ) && ( bus_count == done_buses ))
        {
            break;
        }
    }

    /* ####################
    SUMMARY BLOCK
    #################### */

    for (int i = 0; i < taxi_count; i++)
    {
        taxis[i].track();
    }
    for (int i = 0; i < bus_count; i++)
    {
        buses[i].track();
    }
}