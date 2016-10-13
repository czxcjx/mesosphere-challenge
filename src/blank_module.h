#pragma once
#include "elevator.h"

class BlankModule : public ControlModule {
  public:
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
