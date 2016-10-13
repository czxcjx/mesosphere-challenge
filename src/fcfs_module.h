#pragma once
#include "control_system.h"

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
