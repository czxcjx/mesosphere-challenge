#pragma once
#include "control_system.h"

// Overview: a blank module that does nothing, just asks the elevators to stay still
class BlankModule : public ControlModule {
  public:
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
