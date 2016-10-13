#include "fcfs_module.h"

FCFSModule::FCFSModule(int nElevators) {
  this->targetFloors.resize(nElevators);
  this->currentTime = 0;
  this->currentElevator = 0;
}

vector<ControlOrder> FCFSModule::step(
    vector<Elevator> & elevators, list<PickupRequest> & pickupRequests) {

  // Assign each pickup request cyclically to an elevator
  for (auto request = pickupRequests.rbegin(); request != pickupRequests.rend(); request++) {
    if (request->getTime() != this->currentTime) {
      break;
    }
    this->targetFloors[this->currentElevator].push_back(request->getFloor());
    this->currentElevator = (this->currentElevator + 1) % this->targetFloors.size();
  }
  
  // Move elevators according to goal floors, then to targets
  vector<ControlOrder> orders;
  for (int i = 0; i < elevators.size(); i++) {
    set<int> goals = elevators[i].getGoalFloors();
    if (goals.size() > 0) {
      if (*goals.begin() < elevators[i].getFloor()) {
        orders.push_back(ORDER_DOWN);
      } else {
        orders.push_back(ORDER_UP);
      }
    } else {
      auto target = this->targetFloors[i].begin();
      while (target != this->targetFloors[i].end() && *target == elevators[i].getFloor()) {
        this->targetFloors[i].pop_front();
        target = this->targetFloors[i].begin();
      }
      if (target == this->targetFloors[i].end()) {
        orders.push_back(ORDER_STAY);
      } else if (*target < elevators[i].getFloor()) {
        orders.push_back(ORDER_DOWN);
      } else {
        orders.push_back(ORDER_UP);
      }
    }
  }
  
  this->currentTime++;
  return orders;
}
