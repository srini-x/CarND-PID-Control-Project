# CarND-PID-Controller-Project

## Table of Contents
1. Introduction
2. Concepts
3. Implementation
4. Improvements


## Introduction
The objective of this project is to control the steering angle and the speed of
a car to make it safely navigate around a track. The car that is being
controlled is in a simulated environment provided by Udacity.

The desired steering angle and throttle position are achieved using a technique
called *PID Controller*.

## Concepts
A PID controller works by eliminating or reducing the error between the desired
value and the current value. The error here is called `cte`, short for Cross
Track Error.

PID controller has 3 components

- P
P component is the part that is directly proportional to the error. That means,
higher the error, the intense is the correction.

- D
D component is the 
