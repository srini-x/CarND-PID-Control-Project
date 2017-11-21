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

The whole project works by running 2 different programs. A Udacity simulator
in which there is a race track and a car running on it. Second program is a
C++ program that receives the desired and measured values from the simulator
and sends back corrected values. The steering and throttle values are
continuously corrected using a PID-Controller implemented in `pid.cpp` and
`pid.h`.


### Tuning PID Coefficients

*Twiddle* is a good algorithm to tune the parameters. I implemented the
algorithm in a very clean way. My approach is to measure the number of messages
we get from the simulator for one whole lap around the track. Every time the car completes one
full lap, I update the parameters and collect the `total absolute cte`. Based
on the difference between the `total absolute cte` from the most recent lap and
the `Best total absolute cte` new parameters are calculated.

I decided to tune the parameters manually despite all the time I invested in
implementing the twiddle algorithm because of the following reasons
- The car drives better with manually tuned parameters even if it produces
  higher `total absolute cte`.
- The number of messages in one lap changes from lap to lap. So, I was not able
  to estimate a consistent lap.
- There could be some error/delay in how `cte` is calculated in the simulator.

I was able to drive the car around the track at a maximum speed of *70 mph*. I
also drove the car at default `throttle = 0.3`. I had to use 2 different sets
of parameters to do this. My intuition is that we have to turn the steering a
lot more while driving slow compared to when we are driving faster.

My manually tuned coefficients are:
- Kp: 0.055, Kd: 1.4, Ki: 0.00015 - 70 mph
- Kp: 0.15,  Kd: 1,   Ki: 0.00015 - throttle 0.3

## Results

I ran the simulator at `640x480` resolution and `Fastest` setting for best
performance. My computer has a Core i7-7700k and a Nvidia GTX 1060 6GB.

- Video for my default `throttle = 0.3` - 
- Video for my 70 mph run - 
