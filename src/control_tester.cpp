#include "control_tester.h"
#include <iostream>
using namespace std;

ControlTester::ControlTester(ControlSystem * system) {
  this->system = system;
  this->peopleCount = 0;
  this->unfinishedPeopleCount = 0;
  this->totalWait = 0;
  this->maxWait = 0;
  this->status = system->status();
  this->waitingPeople.resize(system->getFloorCount());
  this->movingPeople.resize(system->getElevatorCount());
}

int ControlTester::getMaxWait() {
  return this->maxWait;
}
float ControlTester::getMeanWait() {
  if (this->peopleCount == 0) {
    return 0;
  } else {
    return (float)this->totalWait / (float)this->peopleCount;
  }
}

void ControlTester::createPerson(int startFloor, int endFloor) {
  if (startFloor == endFloor) {
    return;
  }
  this->peopleCount++;
  this->unfinishedPeopleCount++;
  Person newPerson;
  newPerson.startTime = this->system->getTime();
  newPerson.target = endFloor;
  this->waitingPeople[startFloor - 1].push_back(newPerson);
  Direction direction = (startFloor > endFloor) ? DIR_DOWN : DIR_UP;
  this->system->pickup(startFloor, direction);
}

void ControlTester::step() {
  this->system->step();
  vector<Elevator> newStatus = this->system->status();
  for (int i = 0; i < this->system->getElevatorCount(); i++) {
    int oldFloor = this->status[i].getFloor();
    int newFloor = newStatus[i].getFloor();
    int id = this->status[i].getID();
    if (newFloor != oldFloor) {
      // Pick up waiting people
      for (
          list<Person>::iterator person = this->waitingPeople[oldFloor - 1].begin();
          person != this->waitingPeople[oldFloor - 1].end();
          person++) {

        // If both heading same direction, move person to elevator
        if ((newFloor < oldFloor) == (person->target < oldFloor)) {
          this->system->inputGoal(id, person->target);
          this->movingPeople[i].push_back(*person);
          person = this->waitingPeople[oldFloor - 1].erase(person);
          person--;
        }
      }
      
      // Drop off moving people
      for (
          list<Person>::iterator person = this->movingPeople[i].begin();
          person != this->movingPeople[i].end();
          person++) {
        if (person->target == newFloor) {
          this->unfinishedPeopleCount--;
          person = this->movingPeople[i].erase(person);
          person--;
        }
      }
    }
  }
  this->status = this->system->status();

  
  // Update max wait
  for (int i = 0; i < this->system->getElevatorCount(); i++) {
    for (
        list<Person>::iterator person = this->movingPeople[i].begin();
        person != this->movingPeople[i].end();
        person++) {
      this->maxWait = max(this->maxWait, this->system->getTime() - person->startTime);
    }
  }
  for (int i = 0; i < this->system->getFloorCount(); i++) {
    for (
        list<Person>::iterator person = this->waitingPeople[i].begin();
        person != this->waitingPeople[i].end();
        person++) {
      this->maxWait = max(this->maxWait, this->system->getTime() - person->startTime);
    }
  }

  this->totalWait += this->unfinishedPeopleCount;
}

void ControlTester::printStatus() {
  printf("Step %d: \n", this->system->getTime());
  printf(" Pickup requests:");
  for (auto & request : this->system->getRequests()) {
    printf(" (%d %c)", request.getFloor(), (request.getDirection() == DIR_UP) ? 'U' : 'D');
  }
  printf("\n");
  vector<Elevator> status = this->system->status();
  for (int i = 0; i < this->system->getElevatorCount(); i++) {
    printf(" Elevator %d:\n", status[i].getID());
    printf("  Floor: %d\n", status[i].getFloor());
    printf("  Goals:");
    for (auto & goal : status[i].getGoalFloors()) {
      printf(" %d", goal);
    }
    printf("\n");
    printf("  Carrying people:");
    for (auto & person: this->movingPeople[i]) {
      printf(" [%d]", person.target);
    }
    printf("\n");
  }
  printf(" Waiting people:");
  for (int i = 0; i < this->system->getFloorCount(); i++) {
    for (auto & person : this->waitingPeople[i]) {
      printf(" [%d -> %d]", i + 1, person.target);
    }
  }
  printf("\n\n");
}

void ControlTester::printStats() {
  printf(" Max wait: %d\n", this->getMaxWait());
  printf(" Mean wait: %f\n", this->getMeanWait());
}
