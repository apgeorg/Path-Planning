#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>

class Vehicle
{
public:
    /**
     * @brief The Lane enum Represents the three Hhighway lanes.
     */
    enum Lane
    {
        NONE = -1,
        LEFT = 0,
        MID = 1,
        RIGHT = 2,
    };

    /**
     * @brief Vehicle Constructor, creates an empty Vehicle object.
     */
    Vehicle();

    /**
     * @brief ~Vehicle Desctructor.
     */
    ~Vehicle();

    /**
     * @brief update Updates localization attributes.
     * @param x x position
     * @param y y position
     * @param s frenet s
     * @param d frened d
     * @param yaw yaw angle
     */
    void update(double x, double y, double s, double d, double yaw);

    /**
     * @brief changeLane Checks if lane change is possible.
     * @return true, if lane changed
     */
    bool changeLane();

    /**
     * @brief changeLane Sets lane to new lane.
     * @param newLane Desired lane
     */
    void changeLane(const Vehicle::Lane &newLane);

    /**
     * @brief checkSurroundingCars Checks surrounding cars
     * @param cars List of cars
     * @param prev_size Previous path size
     */
    void checkSurroundingCars(const std::vector<std::vector<int>> &cars, double prev_size);

    /**
     * @brief isCarAhead Checks if any car is ahead.
     * @return true, if car is ahead
     */
    bool isCarAhead() const;

    /**
     * @brief isCarOnLeft Checks if any car is on left side.
     * @return true, if a car is on left side
     */
    bool isCarOnLeft() const;

    /**
     * @brief isCarOnRight Checks if any car is on right side.
     * @return true, if a car is on right side
     */
    bool isCarOnRight() const;

    /**
     * @brief checkLeftLane Checks if left lane is available for change.
     * @return true, if lane changing is possible
     */
    bool checkLeftLane();

    /**
     * @brief checkRightLane Checks if left lane is available for change.
     * @return
     */
    bool checkRightLane();

    Vehicle::Lane getLane() const;
    Vehicle::Lane getLane(const double &d);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getS() const;
    void setS(double value);

    double getD() const;
    void setD(double value);

    double getYaw() const;
    void setYaw(double value);

    double getSpeed() const;
    void setSpeed(double value);

    friend std::ostream &operator<<(std::ostream& out, const Vehicle& vehicle);

private:
    double x;
    double y;
    double s;
    double d;
    double yaw;
    double speed;
    Lane lane;

    bool car_ahead;
    bool car_on_right;
    bool car_on_left;
};

#endif // VEHICLE_H
