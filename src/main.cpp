#include "fcfs_module.h"
#include "control_system.h"
#include "control_tester.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main () {
  FCFSModule module(4);
  ControlSystem system(4, 20, &module);
  ControlTester tester(&system);
  srand(31337);
  for (int i = 0; i < 100; i++) {
    if (i < 15) {
      tester.createPerson(rand() % 20 + 1, rand() % 20 + 1);
    }
    tester.step();
    // tester.printStatus();
  }
  tester.printStats();
  return 0;
}
