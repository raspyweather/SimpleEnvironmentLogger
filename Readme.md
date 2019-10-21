## Idea
There are many cases, when you want to capture environmental data and make use out of it somehow.
Therefore, this project tries to incorporate a couple of sensors in a nice and reuseable pattern.

## Basic Concepts
### Logger
A logger is basicly something, that takes data, errors and messages and provides them to the user. 
Examples in this project are obviously serial logging as well as using the default LED provided on most microcontrollers.
### Sensor
A sensor measures the environment and creates data. In this project, sensor classes should hide everything about how the data is captured and should provide meaningful measurements.
