#include "blank_module.h"

vector<ControlOrder> BlankModule::step(
    vector<Elevator> & elevators, list<PickupRequest> & pickupRequests) {
  vector<ControlOrder> ret;
  for (int i = 0; i < elevators.size(); i++) {
    ret.push_back(ORDER_STAY);
  }
  return ret;
}
