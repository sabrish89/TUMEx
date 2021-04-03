#include "Vehicle.h"

int main()
{
    taxi vehicle(100); // 100 milliseconds per step resolution
    vehicle.track();
    while (true)
    {
        vehicle.move();
        if (vehicle.getState() > 5)
        {
            break;
        }
    }
    vehicle.track();
}