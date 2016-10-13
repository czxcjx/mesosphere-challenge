#pragma once
#include "control_system.h"

// Overview: Search for an existing elevator that is already traveling in the right direction.
// Otherwise, just send a new elevator to do it

// Elevators are either already serving users going up or down,
// or preparing to do so (i.e. going to the highest down or lowest up in a set),
// or idle.
enum ElevatorState {
  STATE_PREP_UP,
  STATE_PREP_DOWN,
  STATE_UP,
  STATE_DOWN,
  STATE_IDLE
};

struct ElevatorData {
  ElevatorState state;
  int target;
};

class GreedyModule : public ControlModule {
  private:
    vector<ElevatorData> elevatorData;
  public:
    GreedyModule(int nElevators);
    vector<ControlOrder> step(
        vector<Elevator> & elevators, list<PickupRequest> & pickupRequests);
};
