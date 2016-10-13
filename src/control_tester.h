#pragma once
#include "control_system.h"

struct Person {
  int startTime;
  int target;
};

class ControlTester {
  private:
    ControlSystem * system;
    vector<list<Person>> waitingPeople;
    vector<list<Person>> movingPeople;
    int peopleCount;
    int unfinishedPeopleCount;
    int totalWait;
    int maxWait;
    vector<Elevator> status;

  public:
    ControlTester(ControlSystem * system);

    int getMaxWait();
    float getMeanWait();

    void createPerson(int startFloor, int endFloor);
    void step();

    void printStatus();
};
