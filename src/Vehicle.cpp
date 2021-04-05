#include <iostream>
#include <iomanip>
#include <limits>
#include <random>
#include <ctime>
#include <cmath>
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(float s, int seed)
/* Initialize a Vehicle with random co-ordinates and direction at t = 0 
Note: step is an input that needs to be resolved at metres per time step duration in seconds
*/
{   
    //srand (static_cast <unsigned> (time(NULL)));
    srand (seed);
    x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(float)3000)); // X [0, 3000]
    y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(float)5000)); // Y [0, 5000]
    th = rand() % static_cast <int>(360); // theta [0,360] // clockwise
    t = 0;
    step = s;
    speed = 1;
    seed = seed;
    distance = 0;
    summary = false;
};

void Vehicle::move()
/* Move vehicle in direction th by one step i.e update (X,Y) in direction th 
Note: ✔TODO: there is a 5 % chance of a direction change within +/-18 % with equal probability
*/
{
    // float rad = ( th * 3.14159265 ) / 180.0;
    // cout << rad << " " << step << endl;
    // srand (seed);
    float pre_x = x;
    float pre_y = y;

    float stride = (float)step * speed * 1000 / 360000; // metres per step milliseconds
    x += stride * cos ( th * 3.14159265 / 180.0 );
    y += stride * sin ( th * 3.14159265 / 180.0 );
    t++;
    
    distance += sqrt(pow(pre_x - x, 2) + pow(pre_y - y, 2));

    // 5 % chance of change of direction within +/-18°
    if (rand() % static_cast <int>(100) < 5)
    {
        if (rand() % static_cast <int>(100) < 50)
        {
            th += rand() % static_cast <int>(18);
            th %= 360;
        }
        else
        {
            th -= rand() % static_cast <int>(18) % 360;
            if (th < 0)
            {
                th = 360 - th;
            }
            th %= 360;
        }
    }
};

void Vehicle::track()
/* getter */
{   
    cout << fixed << setprecision(2) << boolalpha << " X:" << x << " | Y:" << y << " | Direction:" << th << " | Time:" << t << " | In scope: " << bounded() << endl;
};

bool Vehicle::bounded()
/* check if instance is within bounds */
{
    if ( (x > 0 && x < 3000 ) && ( y > 0 && y < 5000 ))
    {
        return true;
    }
    else
    {
        return false;
    }
};

void Vehicle::printSummary(int identifier)
/* print summary details once complete*/
{
    // EMPTY - to be over-riden
};

int Vehicle::getTime()
/* getter */
{
    return step*t / 100;
}

float Vehicle::getDistance()
/* getter */
{
    return distance;
}

privateVehicle::privateVehicle(int resolution, int seed) : Vehicle(resolution, seed)
/* initialize a private vehicle with passengers 
Note: resolution is the number of seconds spend per iteration - simulation time step
*/
{   
    srand (seed);  
    passengers =  1 + rand() % static_cast <int>(4); // passengers [1, 4] in number
    speed = 30 + rand() % static_cast <int>(20); // speed [30, 50] in kph
};

void privateVehicle::move()
/* over-ride move
*/
{
    // Update only if its active
    if ( bounded() == true )
    {
        float pre_x = x;
        float pre_y = y;
        
        // srand (seed);
        float stride = (float)step * speed * 1000 / 360000; // metres per step milliseconds
        x += stride * cos ( th * 3.14159265 / 180.0 );
        y += stride * sin ( th * 3.14159265 / 180.0 );
        t++;

        distance += sqrt(pow(pre_x - x, 2) + pow(pre_y - y, 2));

        // 5 % chance of change of direction within +/-18°
        if (rand() % static_cast <int>(100) < 5)
        {
            if (rand() % static_cast <int>(100) < 50)
            {
                th += rand() % static_cast <int>(18);
                th %= 360;
            }
            else
            {
                th -= rand() % static_cast <int>(18) % 360;
                if (th < 0)
                {
                    th = 360 - th;
                }
                th %= 360;
            }
        }   
    }
};

void privateVehicle::track()
/* over-ride getter */
{   
    cout << fixed << setprecision(2) << boolalpha << " X:" << x << " | Y:" << y << " | Direction:" << th 
    << " | Time:" << t << " | In scope: " << bounded() << " | Passengers:" << passengers << " | Speed: " << speed 
    << " | Distance travelled: " << distance << endl;
};

void privateVehicle::printSummary(int identifier)
/* over-ride */
{
    if (summary == false)
    {
        cout << fixed << setprecision(2) << boolalpha << "Private Vehicle:" << identifier << " | Distance " << distance << " m" << endl;
        summary = true;
    }
};

bus::bus(int resolution, int seed) : Vehicle(resolution, seed)
/* initialize a bus with capacity 
Note: resolution is the number of seconds spend per iteration - simulation time step
*/
{   
    srand (seed);
    capacity =  15 + rand() % static_cast <int>(35); // passengers [15, 50] in number
    speed = 20 + rand() % static_cast <int>(10); // speed [20, 30] in kph
    passengers = 0; // initialize with no passengers
};

void bus::track()
/* over-ride getter */
{   
    cout << fixed << setprecision(2) << boolalpha << " X:" << x << " | Y:" << y << " | Direction:" << th 
    << " | Time:" << t << " | In scope: " << bounded() << " | Passengers:" << passengers << " | Speed: " << speed << 
    " | Capacity: " << capacity << " | Distance travelled: " << distance << endl;
};

void bus::move()
/* over-ride move with random passenger alight and entry
TODO: Notify steps to be number of milliseconds per step
*/
{
    // Only update if its active
    if ( bounded() == true )
    {
        float pre_x = x;
        float pre_y = y;
        
        // srand (seed);
        float stride = (float)( step * speed * 1000) / 360000; // metres per step milliseconds
        x += stride * cos ( th * 3.14159265 / 180.0 );
        y += stride * sin ( th * 3.14159265 / 180.0 );
        t++;
        
        distance += sqrt(pow(pre_x - x, 2) + pow(pre_y - y, 2));

        // 5 % chance of change of direction within +/-18°
        if (rand() % static_cast <int>(100) < 5)
        {
            if (rand() % static_cast <int>(100) < 50)
            {
                th += rand() % static_cast <int>(18);
                th %= 360;
            }
            else
            {
                th -= rand() % static_cast <int>(18) % 360;
                if (th < 0)
                {
                    th = 360 - th;
                }
                th %= 360;
            }
        }

        // Random passenger alight and entry every 5 mins
        if ( ( (t-1)*step % 30000 ) > ( t*step % 30000 ) ) // just passed logic
        {
            // alight
            if (passengers > 0)
            {
                passengers -= rand() % static_cast <int>(passengers); // random exit [0, current_passengers]
            }
            // enter
            if (capacity - passengers > 0)
            {
                passengers += rand() % static_cast <int>(capacity - passengers); // random entry [0, current_capacity]
            }
            // cout << "Passengers altered: " << passengers << " | " << t-1 << "-" << t << endl; // for tracing and debugging
        }
    }
};

void bus::printSummary(int identifier)
/* over-ride */
{
    if (summary == false)
    {
        cout << fixed << setprecision(2) << boolalpha << "Bus:" << identifier << " | Distance " << distance << " m | Current Occupancy " 
        << (float)passengers / capacity << endl;
        summary = true;
    }
};


taxi::taxi(int resolution, int seed) : Vehicle(resolution, seed)
/* initialize a taxi with free state 
Note: resolution is the number of seconds spend per iteration - simulation time step
*/
{   
    srand (seed);
    speed = 40 + rand() % static_cast <int>(20); // speed [40, 60] in kph
    state = 0;
    t_h = 0;
};

void taxi::track()
/* over-ride getter */
{   
    cout << fixed << setprecision(2) << boolalpha << " X:" << x << " | Y:" << y << " | Direction:" << th 
    << " | Time:" << t << " | In scope: " << bounded() << " | State:" << state << " | Speed: " << speed << 
    " | Time hired: " << t_h << " | Distance travelled: " << distance << endl;
};

int taxi::getState()
/*getter for state*/
{
    return state;
}

void taxi::move()
/* over-ride move
*/
{
    if (state < 6) // only update if its active
    {   
        float pre_x = x;
        float pre_y = y;
        
        // srand (seed);
        float stride = (float)( step * speed * 1000 ) / 360000; // metres per step milliseconds
        x += stride * cos ( th * 3.14159265 / 180.0 );
        y += stride * sin ( th * 3.14159265 / 180.0 );
        t++;
        
        distance += sqrt(pow(pre_x - x, 2) + pow(pre_y - y, 2));

        // 5 % chance of change of direction within +/-18°
        if (rand() % static_cast <int>(100) < 5)
        {
            if (rand() % static_cast <int>(100) < 50)
            {
                th += rand() % static_cast <int>(18);
                th %= 360;
            }
            else
            {
                th -= rand() % static_cast <int>(18) % 360;
                if (th < 0)
                {
                    th = 360 - th;
                }
                th %= 360;
            }
            //cout << "Direction has changed to : " << th << endl;
        }
        
        // 1 % chance of getting hired
        if (rand() % static_cast <int>(100) < 1)
        {
            if (( state % 2 == 0 ) && ( state < 6 ))
            {
                state++;
                // cout << "Status has changed to: " << state << endl; // for tracing and debugging
            }
        }

        // if hired and reach bounds, light mirror + free
        if ( ( bounded() != true ) && ( state%2 != 0 ) ) // if instance is currently out of bounds and is hired 
        {
            state++;
            // cout << "Status has changed to: " << state << " with x " << x << " and y " << y << endl; // for tracing and debugging
            // mirror light
            /*idea: angle of incidence with plane of reflection = angle of reflection with plane of reflection
            [0, 180] X: 180-th  Y: 360-th
                else X: 540-th  Y: 360-th
            */
            // cout << "Direction was : " << th << endl; // for tracing and debugging
            if (th <= 180)
            {
                if ((x >= 3000) || (x <= 0))
                {
                    th = 180 - th;
                }
                else
                {
                    th = 360 - th;
                }
            }
            else
            {
                if ((x >= 3000) || (x <= 0))
                {
                    th = 540 - th;
                }
                else
                {
                    th = 360 - th;
                }
            }
            // cout << "Direction has changed to : " << th << endl; // for tracing and debugging
        }

        // if free and out of bounds --- I segregate the two in diff if clauses for ease of case handling
        if ( ( bounded() != true ) && ( state == 0 ) )
        {
            // cout << "Direction was : " << th << endl; // for tracing and debugging
            if (th <= 180)
            {
                if ((x >= 3000) || (x <= 0))
                {
                    th = 180 - th;
                }
                else
                {
                    th = 360 - th;
                }
            }
            else
            {
                if ((x >= 3000) || (x <= 0))
                {
                    th = 540 - th;
                }
                else
                {
                    th = 360 - th;
                }
            }
            // cout << "Direction has changed to : " << th << endl; // for tracing and debugging
        }

        // update the hired times
        if (state%2 != 0)
        {
            t_h++;
        }
    }
};

void taxi::printSummary(int identifier)
/* over-ride */
{
    if (summary == false)
    {
        cout << fixed << setprecision(2) << boolalpha<< "Taxi:" << identifier << " | Distance " << distance << " m | Hired Time " 
        << t_h*step / 100 << " sec | Free Time " << (t-t_h)*step / 100 << " sec" << endl;
        summary = true;
    }
};
