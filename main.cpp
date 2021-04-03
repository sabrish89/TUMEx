#include "Vehicle.h"

int main()
{
    privateVehicle vehicle(100); // 100 milliseconds per step resolution
    vehicle.track();
    while (true)
    {
        vehicle.move();
        if (vehicle.bounded() != true)
        {
            break;
        }
    }
    vehicle.track();
}