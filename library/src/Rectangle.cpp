/**
 * @file Rectangle.cpp
 * @brief Implements the axis-aligned rectangle as an implicit geometry.
 */

#include "Rectangle.hpp"

namespace implicit
{

/**
 * @brief Constructs a rectangle with two corner points.
 *
 * The rectangle is axis-aligned and defined by `(x1, y1)` (lower-left)
 * and `(x2, y2)` (upper-right) coordinates.
 *
 * @param x1 Left boundary (min x)
 * @param y1 Bottom boundary (min y)
 * @param x2 Right boundary (max x)
 * @param y2 Top boundary (max y)
 */
Rectangle::Rectangle(double x1, double y1, double x2, double y2)
        : x1_(x1), x2_(x2), y1_(y1), y2_(y2)
{ }

/**
 * @brief Checks whether a given point lies inside the rectangle.
 *
 * @param x X-coordinate of the query point
 * @param y Y-coordinate of the query point
 * @return true if the point is within or on the boundary of the rectangle
 */
bool Rectangle::inside(double x, double y) const
{
    return x >= x1_ && x <= x2_ && y >= y1_ && y <= y2_;
}

} // namespace implicit
