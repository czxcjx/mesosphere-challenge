#pragma once
#include <list>
#include <set>
#include <vector>
using namespace std;

enum Direction {
  DIR_UP,
  DIR_DOWN
};

class Elevator {
  friend class ControlSystem;
  protected:
    int floor;
    int ID;
    set<int> goalFloors;

  public:
    Elevator(int ID);
    int getFloor();
    int getID();
    set<int> getGoalFloors();
};

class PickupRequest {
  friend class ControlSystem;
  private:
    int time;

  protected:
    int floor;
    Direction direction;

  public:
    PickupRequest(int time, int floor, Direction direction);
    int getTime();
    int getFloor();
    Direction getDirection();
};

enum ControlOrder {
  ORDER_UP,
  ORDER_DOWN,
  ORDER_STAY
};

class ControlModule {
  public:
    virtual vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests) = 0;
};

class ControlSystem {
  private:
    int currentTime;
    int floorCount;
    vector<Elevator> elevators;
    list<PickupRequest> pickupRequests;
    ControlModule * module;

  public:
    ControlSystem(int nElevators, int nFloors, ControlModule * module);
    vector<Elevator> status();
    list<PickupRequest> getRequests();
    int getElevatorCount();
    int getFloorCount();
    int getTime();
    void inputGoal(int ID, int floor);
    void pickup(int floor, Direction direction);
    void step();
};
