#include "Vehicle.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

float mean(float arr[], int len)
{
    if (len <= 0)
    {
        return 0;
    }
    else
    {
        float sum;
        for (int i = 0; i < len; i++)
        {
            sum += arr[i];
        }
        return sum / len;
    }
};

float stdDev(float arr[], int len, float mean)
{
    if (len <= 1)
    {
        return 0;
    }
    else
    {
        float sqsum;
        for (int i = 0; i < len; i++)
        {
            sqsum += pow(arr[i] - mean,2);
        }
        return sqrt(sqsum / ( len - 1 ));
    }
};

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
    
    priv_count = (int)floor(0.85 * agents);
    taxi_count = (int)round(0.10 * agents);
    buss_count = agents - priv_count - taxi_count;
    // cout << priv_count << endl << taxi_count << endl << buss_count << endl << resolution << endl; // for trace and debugging
    if (agents < 20)
    {   
        if ( ( agents <= 0 ) || ( resolution <= 0 ) )
        {
            cout << "step-resolution and number-of-agents must be positive(> 0) integers" << endl;
            return 0;
        }
        else
        {
            cout << "WARNING: proportions decided may be unrepresentative due to low number of agents" << endl;
        }
    }

    /* ####################
    INIT BLOCK 
    #################### */
    
    cout << endl << "SIMULATING:" << endl << endl;
    srand (static_cast <unsigned> (time(NULL))); // Master seed
    // Private vehicles
    vector<privateVehicle> privs;
    for (int i = 0; i < priv_count; i++)
    {
        privs.push_back(privateVehicle(resolution, rand()%1000));
        // privs[i].track();
    }
    // Taxis
    vector<taxi> taxis;
    for (int i = 0; i < taxi_count; i++)
    {
        taxis.push_back(taxi(resolution, rand()%1000));
        // taxis[i].track();
    }
    // Buses
    vector<bus> buses;
    for (int i = 0; i < buss_count; i++)
    {
        buses.push_back(bus(resolution, rand()%1000));
        // buses[i].track();
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
                    taxis[i].printSummary(i);
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
                    buses[i].printSummary(i);
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
                    privs[i].printSummary(i);
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

    cout << endl << "SUMMARY:" << endl << endl;

    float distP[priv_count];
    float timeP[priv_count];

    float distT[taxi_count];
    float timeT[taxi_count];

    float distB[buss_count];
    float timeB[buss_count];

    for (int i = 0; i < priv_count; i++)
    {
        distP[i] = privs[i].getDistance();
        timeP[i] = privs[i].getTime();
    }
    for (int i = 0; i < taxi_count; i++)
    {
        distT[i] = taxis[i].getDistance();
        timeT[i] = taxis[i].getTime();
    }
    for (int i = 0; i < buss_count; i++)
    {
        distB[i] = buses[i].getDistance();
        timeB[i] = buses[i].getTime();
    }

    cout << endl << "TAXIS:" << endl;
    cout << "Trip Length" << endl;
    cout << "Avg: " << mean(distT, taxi_count) << " m | Std.dev: " << stdDev(distT, taxi_count, mean(distT, taxi_count)) << " m" << endl;
    cout << "Travel Time" << endl;
    cout << "Avg: " << mean(timeT, taxi_count) << " sec | Std.dev: " << stdDev(timeT, taxi_count, mean(timeT, taxi_count)) << " sec" << endl;

    cout << endl << "BUSES:" << endl;
    cout << "Trip Length" << endl;
    cout << "Avg: " << mean(distB, buss_count) << " m | Std.dev: " << stdDev(distB, buss_count, mean(distB, buss_count)) << " m" << endl;
    cout << "Travel Time" << endl;
    cout << "Avg: " << mean(timeB, buss_count) << " sec | Std.dev: " << stdDev(timeB, buss_count, mean(timeB, buss_count)) << " sec" << endl;

    cout << endl << "PRIVATE VEHICLES:" << endl;
    cout << "Trip Length" << endl;
    cout << "Avg: " << mean(distP, priv_count) << " m | Std.dev: " << stdDev(distP, priv_count, mean(distP, priv_count)) << " m" << endl;
    cout << "Travel Time" << endl;
    cout << "Avg: " << mean(timeP, priv_count) << " sec | Std.dev: " << stdDev(timeP, priv_count, mean(timeP, priv_count)) << " sec" << endl;

}