#pragma once
#include "control_system.h"

class DirectionalModule : public ControlModule {
  public:
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
