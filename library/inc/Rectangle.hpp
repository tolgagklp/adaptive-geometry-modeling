#pragma once

/**
 * @file Rectangle.hpp
 * @brief Defines a 2D axis-aligned rectangle as an implicit geometry.
 */

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

/**
 * @class Rectangle
 * @brief Represents an axis-aligned rectangle using implicit geometry.
 *
 * The rectangle is defined by its corner coordinates `(x1, y1)` and `(x2, y2)`.
 * It inherits from AbsImplicitGeometry and provides an implementation of the `inside` method.
 */
class Rectangle : public AbsImplicitGeometry
{
private:
    double x1_;  ///< Lower x-bound (left)
    double x2_;  ///< Upper x-bound (right)
    double y1_;  ///< Lower y-bound (bottom)
    double y2_;  ///< Upper y-bound (top)

public:
    /**
     * @brief Constructs a Rectangle with two opposite corners.
     *
     * @param x1 X-coordinate of first corner (left)
     * @param y1 Y-coordinate of first corner (bottom)
     * @param x2 X-coordinate of opposite corner (right)
     * @param y2 Y-coordinate of opposite corner (top)
     */
    Rectangle(double x1, double y1, double x2, double y2);

    /**
     * @brief Checks if a given point lies inside the rectangle.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside, false otherwise
     */
    bool inside(double x, double y) const override;
};

} // namespace implicit
