Mesosphere Intern Challenge
===========================

## Overview

This implements an elevator control system as described [here](https://mesosphere.com/jobs/challenges/intern/index.html). It includes the following:

* Time-steppable simulation of the elevator system
* Pluggable modules for elevator control logic
* Testing module which simulates people riding the elevators and calculating their waiting time

## Build Instructions
```
make
bin/main
```

## Source code overview

There are 3 main parts to the source code:
* **control_system.cpp** implements the main elevator control system. This will read control orders from a control module, moving the elevators up and down as instructed. It also maintains the state of the elevators' current positions and a list of goal floors (i.e. pressed buttons inside the elevator), as well as a list of pickup requests (i.e. pressed buttons from outside the elevator).
* **control_tester.cpp** implements a testing and profiling module. This simulates people who wish to get from floor to floor using the elevator, keeping track of their waiting times.
* Algorithmic modules (**blank_module.cpp**, **fcfs_module.cpp**, etc.) implement an algorithm to move the elevators around, responding to button presses, etc.

## Control system
The control system keeps track of a vector of **Elevator**s and a list of **PickupRequest**s. Each **Elevator** moves according to the **ControlModule**'s (described below) instructions every time the **step()** function is called. A pickup request comprises of a floor, starting time and a direction and will be fulfilled when an elevator moves in the correct direction away from the corresponding floor. An elevator will keep track of an integer ID, the current floor, and a set of "goal floors", which can be thought of as the set of buttons currently lit up inside the elevator. A goal floor will be removed from the elevator whenever it reaches the corresponding floor.

## Control module API
To create a new algorithmic module, inherit from the **ControlModule** abstract class and implement the **step** function (described below), which is called whenever the **step()** function is called in the control system.

#### Giving orders
Every algorithmic module must implement the **vector<ControlOrder> step(vector<Elevators> & elevator, list<PickupRequest> & pickupRequest)** function. This processes the state of all elevators and pickup requests and returns a vector of **ControlOrder**s. Each **ControlOrder** is either **ORDER_UP**, **ORDER_DOWN**, or **ORDER_STAY**, corresponding to the direction which each elevator should move in the next time step.

## Control tester API

#### Creating new people
The function **createPerson(int startFloor, int endFloor)** creates a new person who wants to get from the starting floor to the ending floor. The person will automatically enter the first elevator that passes their floor traveling in the correct direction, pressing the corresponding button inside the elevator, then getting off when the elevator reaches the desired destination.

#### Statistics
The functions **getMaxWait()**, **getMeanWait()**, and **printStats()** will return/print the corresponding statistics about people's waiting times.
