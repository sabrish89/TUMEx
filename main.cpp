#include "Vehicle.h"
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main()
{   
    /* ####################
    USER I/P BLOCK
    #################### */

    int resolution;
    int agents;
    cout << "Enter step resolution in milliseconds" << endl;
    cin >> resolution;
    cout << "Enter number of agents" << endl;
    cin >> agents;

    /* ####################
    I/P PRE-PROCESSING & VALIDATION BLOCK
    #################### */

    int priv_count; // 85 % of agents
    int taxi_count; // 10 % of agents
    int buss_count; // 05 % of agents
    
    

    /* ####################
    INIT BLOCK 
    #################### */
    
    srand (static_cast <unsigned> (time(NULL))); // Master seed
    // Private vehicles
    vector<privateVehicle> privs;
    for (int i = 0; i < priv_count; i++)
    {
        privs.push_back(privateVehicle(100, rand()%agents));
        privs[i].track();
    }
    // Taxis
    vector<taxi> taxis;
    for (int i = 0; i < taxi_count; i++)
    {
        taxis.push_back(taxi(100, rand()%agents));
        taxis[i].track();
    }
    // Buses
    vector<bus> buses;
    for (int i = 0; i < buss_count; i++)
    {
        buses.push_back(bus(100, rand()%agents));
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
        if (buss_count > done_buses)
        {
            for (int i = 0; i < buss_count; i++)
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
        // Private vehicles
        int done_privs = 0;
        if (priv_count > done_privs)
        {
            for (int i = 0; i < priv_count; i++)
            {
                if (privs[i].bounded() != true)
                {
                    done_privs++;
                }
                else
                {
                    privs[i].move();
                }
            }
        }
        // SIM breaker
        if ( ( taxi_count == done_taxis ) && ( buss_count == done_buses ) && ( priv_count == done_privs ) )
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