/**
 * @file Difference.cpp
 * @brief Implements the CSG difference operation (A \ B) for implicit geometries.
 */

#include "Difference.hpp"

namespace implicit
{

/**
 * @brief Constructs a difference operation between two implicit geometries.
 *
 * The resulting shape contains points that are inside the first operand
 * but outside the second operand.
 *
 * @param operand1 The geometry to subtract from (minuend)
 * @param operand2 The geometry to subtract (subtrahend)
 */
Difference::Difference(ImplicitGeometryPtr operand1,
                       ImplicitGeometryPtr operand2)
        : AbsOperation(operand1, operand2)
{ }

/**
 * @brief Checks if a point lies in the difference (A \ B) of the two geometries.
 *
 * @param x X-coordinate of the query point
 * @param y Y-coordinate of the query point
 * @return true if the point is inside operand1 and not inside operand2
 */
bool Difference::inside(double x, double y) const
{
    return operand1_->inside(x, y) && !operand2_->inside(x, y);
}

} // namespace implicit
