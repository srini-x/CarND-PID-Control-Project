# CarND-PID-Controller-Project

## Table of Contents
1. Introduction
2. Concepts
3. Implementation
4. Results
5. Improvements


## Introduction
The objective of this project is to control the steering angle and the speed of
a car to make it safely navigate around a track. The car that is being
controlled is in a simulated environment provided by Udacity.

The desired steering angle and throttle position are achieved using a technique
called *PID Controller*.

## Concepts
A PID controller is a type of feedback system that works by eliminating or reducing the error between the desired
value and the current measured value. The error here is called CTE, short for Cross
Track Error. 

### PID controller has 3 components
CTE is eliminated by applying a correction which includes a proportional(P) component, Integral(I) component, and a Derivative(D) component. 

#### P Component
P component is the part that is directly proportional to the error. That means,
higher the error, the intense is the correction.

P-controller is enough to reduce the error but it can not keep the error at a stable condition. It overshoots the target and again corrects for the error in the opposite direction which causes oscillations.

#### D Component
D component is proportional to the rate of change of the error.

PD-controller helps to reduce the oscillations created by the P controller by reducing the rate of change of error close to 0.

#### I Component
I component is proportional to the total error measured from all the time steps.

PD controller can bring the error close to 0 and keep it from oscillating. However, it may not be able to completely eliminate the error because of a bias in the system. I-controller is used to help close the final gap by nullifying the error caused by a bias in the system.

### PID Coefficients

`Kp`, `Ki`, and `Kd` are used as the coefficients for the `P`, `I`, and `D` terms respectively. These coefficients are chosen carefully to get the optimum performance out of the PID-controller

### PID-Controller Equation
Given the error as `cte`, differential of the error as `cte_d`, and integral of the error as `cte_i`, output of a PID-controller with coefficients `Kp`, `Kd`, and `Ki` is expressed as

`pid_out = Kp * cte + Kd * cte_d + Ki * cte_i`


## Implementation



