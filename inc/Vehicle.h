#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle
{
protected:
    float x;
    float y;
    int step; // Number of milliseconds per iteration step
    int speed;
    int t;
    int th;
    int seed;
    float distance;

public:
    Vehicle(float s, int seed);
    void move();
    void track();
    bool bounded();
};

class privateVehicle : public Vehicle
{
protected:
    int passengers;
public:
    privateVehicle(int resolution, int seed);
    void move();
    void track();
};

class bus : public Vehicle
{
protected:
    int capacity;
    int passengers;
public:
    bus(int resolution, int seed);
    void track();
    void move();
};

class taxi : public Vehicle
{
protected:
    int state; // 0,2,4 - free | 1,3,5 - hired
    int t_h;
public:
    taxi(int resolution, int seed);
    void track();
    int getState();
    void move();
};

#endif