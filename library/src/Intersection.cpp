/**
 * @file Intersection.cpp
 * @brief Implements the CSG intersection operation for implicit geometries.
 */

#include "Intersection.hpp"

namespace implicit
{

/**
 * @brief Constructs an intersection operation between two implicit geometries.
 *
 * The resulting shape contains only the region that lies inside both operands.
 *
 * @param operand1 First operand geometry
 * @param operand2 Second operand geometry
 */
Intersection::Intersection(ImplicitGeometryPtr operand1,
                           ImplicitGeometryPtr operand2)
        : AbsOperation(operand1, operand2)
{ }

/**
 * @brief Checks if a point lies in the intersection of the two geometries.
 *
 * @param x X-coordinate of the query point
 * @param y Y-coordinate of the query point
 * @return true if the point is inside both operand1 and operand2
 */
bool Intersection::inside(double x, double y) const
{
    return operand1_->inside(x, y) && operand2_->inside(x, y);
}

} // namespace implicit
