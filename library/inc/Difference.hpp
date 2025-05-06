#pragma once

/**
 * @file Difference.hpp
 * @brief Defines the CSG operation for set difference between two implicit geometries.
 */

#include "AbsOperation.hpp"

namespace implicit
{

/**
 * @class Difference
 * @brief Represents the set difference (A \ B) of two implicit geometries.
 *
 * A point is considered inside the result if it lies in the first operand
 * but **not** in the second operand. This class inherits from AbsOperation
 * and overrides the `inside` method accordingly.
 */
class Difference : public AbsOperation
{
public:
    /**
     * @brief Constructs a difference operation between two geometries.
     *
     * @param operand1 First input geometry (minuend)
     * @param operand2 Second input geometry (subtrahend)
     */
    Difference(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);

    /**
     * @brief Checks whether a point lies inside the difference of the operands.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside the first operand and not in the second
     */
    bool inside(double x, double y) const override;
};

} // namespace implicit
