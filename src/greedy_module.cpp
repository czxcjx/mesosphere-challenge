#include "greedy_module.h"
#include <cstdio>
using namespace std;

GreedyModule::GreedyModule(int nElevators) {
  this->elevatorData.resize(nElevators);
  for (int i = 0; i < nElevators; i++) {
    this->elevatorData[i].target = 1;
    this->elevatorData[i].state = STATE_IDLE;
  }
}

int getPriority(Elevator & elevator, PickupRequest & request, ElevatorData & data) {
  if (request.getDirection() == DIR_UP) {
    // Already traveling up with people
    if (data.state == STATE_UP && request.getFloor() >= elevator.getFloor()) {
      return 1;

    // Preparing to travel up without people
    } else if (data.state == STATE_PREP_UP) {
      return 2;

    // Idling
    } else if (data.state == STATE_IDLE) {
      return 0;
    }
  } else {
    // Already traveling down with people
    if (data.state == STATE_DOWN && request.getFloor() <= elevator.getFloor()) {
      return 1;

    // Preparing to travel down without people
    } else if (data.state == STATE_PREP_DOWN) {
      return 2;

    // Idling
    } else if (data.state == STATE_IDLE) {
      return 0;
    }
  }
  return 3;
}

vector<ControlOrder> GreedyModule::step(
    vector<Elevator> & elevators, list<PickupRequest> & pickupRequests) {

  for (auto request = pickupRequests.begin(); request != pickupRequests.end(); request++) {
    int bestElevator = -1;
    int bestPriority = 3;
    for (int i = 0; i < elevators.size(); i++) {
      int priority = getPriority(elevators[i], *request, this->elevatorData[i]);
      if (priority < bestPriority) {
        bestElevator = i;
        bestPriority = priority;
      }
    }
    if (bestElevator == -1) {
      continue;
    }
    if (request->getDirection() == DIR_UP && this->elevatorData[bestElevator].target > request->getFloor()) {
      this->elevatorData[bestElevator].target = request->getFloor();
      if (this->elevatorData[bestElevator].state == STATE_IDLE) {
        this->elevatorData[bestElevator].state = STATE_PREP_UP;
      }
    }
    if (request->getDirection() == DIR_DOWN && this->elevatorData[bestElevator].target < request->getFloor()) {
      this->elevatorData[bestElevator].target = request->getFloor();
      if (this->elevatorData[bestElevator].state == STATE_IDLE) {
        this->elevatorData[bestElevator].state = STATE_PREP_UP;
      }
    }
  }

  vector<ControlOrder> orders;
  for (int i = 0; i < elevators.size(); i++) {
    set<int> goalFloors = elevators[i].getGoalFloors();
    if (goalFloors.size() > 0) {
      if (*goalFloors.begin() < elevators[i].getFloor()) {
        this->elevatorData[i].state = STATE_DOWN;
        this->elevatorData[i].target = min(this->elevatorData[i].target, *goalFloors.begin());
      } else {
        this->elevatorData[i].state = STATE_UP;
        this->elevatorData[i].target = max(this->elevatorData[i].target, *goalFloors.begin());
      }
    }
    if (this->elevatorData[i].state == STATE_DOWN) {
      if (goalFloors.size() == 0 && elevatorData[i].target >= elevators[i].getFloor()) {
        this->elevatorData[i].state = STATE_IDLE;
        this->elevatorData[i].target = elevators[i].getFloor();
      }
    }
    if (this->elevatorData[i].state == STATE_UP) {
      if (goalFloors.size() == 0 && elevatorData[i].target <= elevators[i].getFloor()) {
        this->elevatorData[i].state = STATE_IDLE;
        this->elevatorData[i].target = elevators[i].getFloor();
      }
    }
    if (this->elevatorData[i].state == STATE_PREP_DOWN || this->elevatorData[i].state == STATE_PREP_UP) {
      if (goalFloors.size() == 0 && elevatorData[i].target == elevators[i].getFloor()) {
        this->elevatorData[i].state = (this->elevatorData[i].state == STATE_PREP_DOWN) ? STATE_DOWN : STATE_UP;
      }
    }


    if (this->elevatorData[i].state == STATE_DOWN || this->elevatorData[i].target < elevators[i].getFloor()) {
      orders.push_back(ORDER_DOWN);
    } else if (this->elevatorData[i].state == STATE_UP || this->elevatorData[i].target > elevators[i].getFloor()) {
      orders.push_back(ORDER_UP);
    } else {
      orders.push_back(ORDER_STAY);
    }
  }
  return orders;
}
