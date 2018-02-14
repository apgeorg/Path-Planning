#include "vehicle.h"

#include <math.h>

Vehicle::Vehicle() :
    x(0.0), y(0.0), s(0.0), d(0.0), yaw(0.0), speed(0.0), lane(Lane::NONE), car_ahead(false), car_on_left(false), car_on_right(false)
{
    this->lane = getLane(d);
}

Vehicle::~Vehicle()
{
}

void Vehicle::update(double x, double y, double s, double d, double yaw)
{
    this->x = x;
    this->y = y;
    this->s = s;
    this->d = d;
    this->yaw = yaw;
    this->lane = getLane(d);
    car_ahead = false;
    car_on_left = false;
    car_on_right = false;
}

bool Vehicle::changeLane()
{
    // Prefer always left
    if (checkLeftLane())
    {
        lane = static_cast<Vehicle::Lane>(lane-1);
        return true;
    }
    else if (checkRightLane())
    {
        lane = static_cast<Vehicle::Lane>(lane+1);
        return true;
    }
    return false;
}

void Vehicle::changeLane(const Vehicle::Lane &newLane)
{
    lane = newLane;
}

void Vehicle::checkSurroundingCars(const std::vector<std::vector<int> > &cars, double prev_size)
{
    for (int i = 0; i < cars.size(); ++i)
    {
        double d = cars[i][6];

        // Don't  waste performance..
        if (d < 0)
            continue;

        int id = cars[i][0];
        Vehicle::Lane lane = getLane(d);
        double vx = cars[i][3];
        double vy = cars[i][4];
        double check_speed = sqrt(vx*vx+vy*vy);
        double check_car_s = cars[i][5];
        // Estimate car s position after executing previous trajectory.
        check_car_s+=((double)prev_size*.02*check_speed);

        if (lane == this->lane)
        {
          car_ahead |= (check_car_s > s) && ((check_car_s - s) < 30);
          //std::cout << "Car " << id << " ahead!" << std::endl;
        }
        else if (lane - this->lane == -1)
        {
          car_on_left |= ((s - 30) < check_car_s) && ((s + 30) > check_car_s);
          //std::cout << "Car " << id << " on left side!" << std::endl;
        }
        else if (lane - this->lane == 1)
        {
          car_on_right |= ((s - 30) < check_car_s) && ((s + 30) > check_car_s);
          //std::cout << "Car " << id << " on right side!" << std::endl;
        }
    }
}

bool Vehicle::isCarAhead() const
{
    return car_ahead;
}

bool Vehicle::isCarOnLeft() const
{
    return car_on_left;
}

bool Vehicle::isCarOnRight() const
{
    return car_on_right;
}

bool Vehicle::checkLeftLane()
{
    return !car_on_left && (lane != Vehicle::Lane::LEFT);
}

bool Vehicle::checkRightLane()
{
    return !car_on_right && (lane != Vehicle::Lane::RIGHT);
}

double Vehicle::getY() const
{
    return y;
}

void Vehicle::setY(double value)
{
    y = value;
}

double Vehicle::getS() const
{
    return s;
}

void Vehicle::setS(double value)
{
    s = value;
}

double Vehicle::getD() const
{
    return d;
}

void Vehicle::setD(double value)
{
    d = value;
}

double Vehicle::getYaw() const
{
    return yaw;
}

void Vehicle::setYaw(double value)
{
    yaw = value;
}

double Vehicle::getSpeed() const
{
    return speed;
}

void Vehicle::setSpeed(double value)
{
    speed = value;
}

Vehicle::Lane Vehicle::getLane() const
{
    return lane;
}

Vehicle::Lane Vehicle::getLane(const double &d)
{
    if ((d > 0) && (d < 4))
      return Lane::LEFT;
    else if ((d > 4) && (d < 8))
      return Lane::MID;
    else if ((d > 8) && (d < 12))
      return Lane::RIGHT;
   else
      return Lane::NONE;
}

double Vehicle::getX() const
{
    return x;
}

void Vehicle::setX(double value)
{
    x = value;
}

std::ostream& operator<<(std::ostream &out, const Vehicle &vehicle)
{
    out << "------------------------------------------" << std::endl;
    out << "X: " << vehicle.x  << ", Y: " << vehicle.y << std::endl;
    out << "S: " << vehicle.s  << ", D: " << vehicle.d << std::endl;
    out << "Lane: " << (int)vehicle.lane << std::endl;
    out << "Speed:" << vehicle.speed << ",  Yaw: " << vehicle.yaw << std::endl;
    out << "------------------------------------------" << std::endl;
}
