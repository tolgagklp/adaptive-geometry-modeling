#pragma once

/**
 * @file Circle.hpp
 * @brief Defines a 2D implicit circle geometry.
 */

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

/**
 * @class Circle
 * @brief Represents a 2D circle using implicit geometry.
 *
 * The circle is defined by its center coordinates `(x, y)` and radius `r`.
 * Inherits from AbsImplicitGeometry and implements the `inside` method.
 */
class Circle : public AbsImplicitGeometry
{
private:
    double x_;  ///< X-coordinate of the center
    double y_;  ///< Y-coordinate of the center
    double r_;  ///< Radius of the circle

public:
    /**
     * @brief Constructs a Circle object.
     *
     * @param x X-coordinate of the center
     * @param y Y-coordinate of the center
     * @param radius Radius of the circle
     */
    Circle(double x, double y, double radius);

    /**
     * @brief Checks if a given point lies inside the circle.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside, false otherwise
     */
    bool inside(double x, double y) const override;
};

} // namespace implicit
