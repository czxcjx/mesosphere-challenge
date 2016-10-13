#pragma once
#include "control_system.h"

class BlankModule : public ControlModule {
  public:
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
