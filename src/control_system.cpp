#include "elevator.h"

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
  this->floors = nFloors;
  for (int i = 0; i < nElevators; i++) {
    this->elevators.push_back(Elevator(i));
  }
  this->module = module;
}

vector<Elevator> ControlSystem::status() {
  return this->elevators;
}

void ControlSystem::pickup(int floor, Direction direction) {
  if (floor <= 0 || floor > this->floors) {
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

    // Search through pickup requests and goal floors and delete current 
    // floor
    if (orders[i] == ORDER_STAY) {
      for (auto request = this->pickupRequests.begin(); 
          request != this->pickupRequests.end(); 
          request++) {
        if (request->floor == currentFloor) {
          request = this->pickupRequests.erase(request);
        }
      }
      this->elevators[i].goalFloors.erase(currentFloor);

    // Go up or down as directed
    } else if (orders[i] == ORDER_UP) {
      if (currentFloor + 1 <= this->floors) {
        this->elevators[i].floor++;
      }
    } else if (orders[i] == ORDER_DOWN) {
      if (currentFloor - 1 > 0) {
        this->elevators[i].floor--;
      }
    }
  }
}
