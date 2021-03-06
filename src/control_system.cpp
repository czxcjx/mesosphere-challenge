#include "control_system.h"

Elevator::Elevator(int ID) {
  this->ID = ID;
  this->floor = 1;
}

int Elevator::getFloor() {
  return this->floor;
}

int Elevator::getID() {
  return this->ID;
}

set<int> Elevator::getGoalFloors() {
  set<int> ret = this->goalFloors;
  return ret;
}

PickupRequest::PickupRequest(int time, int floor, Direction direction) {
  this->time = time;
  this->floor = floor;
  this->direction = direction;
}

int PickupRequest::getTime() {
  return this->time;
}

int PickupRequest::getFloor() {
  return this->floor;
}

Direction PickupRequest::getDirection() {
  return this->direction;
}

ControlSystem::ControlSystem(int nElevators, int nFloors, 
    ControlModule * module) {
  this->currentTime = 0;
  this->floorCount = nFloors;
  for (int i = 0; i < nElevators; i++) {
    this->elevators.push_back(Elevator(i));
  }
  this->module = module;
}

vector<Elevator> ControlSystem::status() {
  return this->elevators;
}

list<PickupRequest> ControlSystem::getRequests() {
  return this->pickupRequests;
}

int ControlSystem::getElevatorCount() {
  return this->elevators.size();
}

int ControlSystem::getFloorCount() {
  return this->floorCount;
}

int ControlSystem::getTime() {
  return this->currentTime;
}

void ControlSystem::pickup(int floor, Direction direction) {
  if (floor <= 0 || floor > this->floorCount) {
    return;
  }
  this->pickupRequests.push_back(
      PickupRequest(this->currentTime, floor, direction));
}

void ControlSystem::inputGoal(int ID, int floor) {
  this->elevators[ID].goalFloors.insert(floor);
}

void ControlSystem::step() {
  vector<ControlOrder> orders = 
    this->module->step(this->elevators, this->pickupRequests);

  for (int i = 0; i < this->elevators.size(); i++) {
    int currentFloor = this->elevators[i].getFloor();
    
    // Erase goal floor
    this->elevators[i].goalFloors.erase(currentFloor);

    // If moving in the right direction, erase requests
    for (auto request = this->pickupRequests.begin(); 
        request != this->pickupRequests.end(); 
        request++) {
      if (request->floor == currentFloor) {
        if ((orders[i] == ORDER_UP && request->direction == DIR_UP) ||
            (orders[i] == ORDER_DOWN && request->direction == DIR_DOWN)) {
          request = this->pickupRequests.erase(request);
          request--;
        }
      }
    }

    // Go up or down as directed
    if (orders[i] == ORDER_UP) {
      if (currentFloor + 1 <= this->floorCount) {
        this->elevators[i].floor++;
      }
    } else if (orders[i] == ORDER_DOWN) {
      if (currentFloor - 1 > 0) {
        this->elevators[i].floor--;
      }
    }
  }
  this->currentTime++;
}
