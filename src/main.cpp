#include "control_system.h"
#include "control_tester.h"
#include "fcfs_module.h"
#include "greedy_module.h"
#include <iostream>
#include <cstdlib>
using namespace std;

const int NUM_ELEVATORS = 8;
const int NUM_FLOORS = 50;
const int NUM_ROUNDS = 10000;

int main () {
  GreedyModule module(NUM_ELEVATORS);
  ControlSystem system(NUM_ELEVATORS, NUM_FLOORS, &module);
  ControlTester tester(&system);
  srand(31337);
  for (int i = 0; i < NUM_ROUNDS; i++) {
    tester.createPerson(rand() % NUM_FLOORS + 1, rand() % NUM_FLOORS + 1);
    tester.step();
    tester.printStatus();
  }
  tester.printStats();
  return 0;
}
