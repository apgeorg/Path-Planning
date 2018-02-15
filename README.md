[image1]: ./images/path-planning.png "Autonomous Driving on a Highway"

# Path Planning

## Overview

The goal of this project is to safely navigate around a virtual highway with other traffic that is driving +-10 MPH of the 50 MPH speed limit.

<p align="center"><img width="540" height="400" src="./images/path-planning.png"></p>

## Model

The overall model can be seperated into 3 main parts:

- Prediction,
- Behavior Planning,
- Trajectory Generation. 

### Prediction

The prediction part deals with the sensor fusion data which contains all the information about the cars on the right-hand side of the road. For each car, its lane,  position and its planned trajectory is considered. Further a lane change is marked as not safe when its distance to our ego vehicle is less than 30 meters in front or behind us.

### Behavior Planning

Based on the predictions of the current situation, the ego vehicle increases or decreases the speed, or decide to change a lane when there are no surrounding cars and the lane exists. Instead of increase/decrease the speed, the difference to the reference speed is noticed and its used for speed changes while generating the trajectory. This approach makes the car more responsive to changing situations like when a car in front of it trying to apply breaks.

### Trajectory Generation

The trajectory generation is based on the speed and lane output from the behavior, car coordinates and previous path points.

First, the last two points of the previous trajectory (or the car position if there are no previous trajectory) are used in conjunction three points at a far distance to initialize the spline calculation. To make the work less complicated to the spline calculation based on those points, the coordinates are transformed (shift and rotation) to local car coordinates.

In order to ensure more continuity on the trajectory (in addition to adding the last two point of the pass trajectory to the spline adjustment), the pass trajectory points are copied to the new trajectory. The rest of the points are calculated by evaluating the spline and transforming the output coordinates to not local coordinates. The speed change is decided on the behavior part of the code, but it is used in that part to increase/decrease speed on every trajectory points instead of doing it for the complete trajectory.

### Limitations

The project is far from perfect and can be improved in many ways. Some limitations are:

There are some rare incidents of accidents happening in the opposite lane and cars ending on the other side of the road. Those cannot be avoided since there are no sensor fusion data for that side of the road.
