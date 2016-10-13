#include "elevator.h"
#include "blank_module.h"
#include <iostream>
using namespace std;

int main () {
  ControlModule * module = new BlankModule();
  ControlSystem system(1, 10, module);
  for (int i = 0; i < 10; i++) {
    system.inputGoal(0, i + 1);
  }
  for (int i = 0; i < 5; i++) {
    system.step();
    printf("Step %d: \n", system.getTime());
    vector<Elevator> status = system.status();
    for (int j = 0; j < status.size(); j++) {
      printf(" Elevator %d:\n", status[j].getID());
      printf("  Floor: %d\n", status[j].getFloor());
      printf("  Goals:");
      for (auto & goal : status[j].getGoalFloors()) {
        printf(" %d", goal);
      }
      printf("\n");
    }
  }
  delete module;
  return 0;
}
