/**
 * @file Union.cpp
 * @brief Implements the CSG union operation for implicit geometries.
 */

#include "Union.hpp"

namespace implicit
{

/**
 * @brief Constructs a union operation between two implicit geometries.
 *
 * The resulting shape includes all points that lie inside either operand.
 *
 * @param operand1 First operand geometry
 * @param operand2 Second operand geometry
 */
Union::Union(ImplicitGeometryPtr operand1,
             ImplicitGeometryPtr operand2)
        : AbsOperation(operand1, operand2)
{ }

/**
 * @brief Checks whether a point lies inside the union of the operands.
 *
 * @param x X-coordinate of the query point
 * @param y Y-coordinate of the query point
 * @return true if the point is inside at least one of the operands
 */
bool Union::inside(double x, double y) const
{
    return operand1_->inside(x, y) || operand2_->inside(x, y);
}

} // namespace implicit
