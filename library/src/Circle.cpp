/**
 * @file Circle.cpp
 * @brief Implements the implicit circle geometry class.
 */

#include "Circle.hpp"
#include <cmath>

namespace implicit
{

/**
 * @brief Constructs a circle with a given center and radius.
 *
 * @param x X-coordinate of the center
 * @param y Y-coordinate of the center
 * @param radius Radius of the circle
 */
Circle::Circle(double x, double y, double radius)
        : x_(x), y_(y), r_(radius)
{ }

/**
 * @brief Checks whether the given point lies inside the circle.
 *
 * Uses the standard Euclidean distance formula.
 *
 * @param x X-coordinate of the query point
 * @param y Y-coordinate of the query point
 * @return true if the point lies inside or on the boundary of the circle
 */
bool Circle::inside(double x, double y) const
{
    double dx = x - x_;
    double dy = y - y_;
    return (dx * dx + dy * dy) <= (r_ * r_);
}

} // namespace implicit
