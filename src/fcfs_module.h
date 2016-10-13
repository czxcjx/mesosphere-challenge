#pragma once
#include "control_system.h"

// Overview: Cyclically allocates new pickup requests to elevators (e.g. 0, 1, 2, 3, 0, ...).
// Each elevator will try to fulfill goal floors from inside itself first, then try to 
// fulfill newly allocated pickup requests.

class FCFSModule : public ControlModule {
  private:
    vector<list<int>> targetFloors;
    int currentTime;
    int currentElevator;
  public:
    FCFSModule(int nElevators);
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
