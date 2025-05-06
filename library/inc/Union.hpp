#pragma once

/**
 * @file Union.hpp
 * @brief Defines the CSG operation for union between two implicit geometries.
 */

#include "AbsOperation.hpp"

namespace implicit
{

/**
 * @class Union
 * @brief Represents the union of two implicit geometries.
 *
 * A point is considered inside the union if it lies in **at least one** of the operand geometries.
 * This class inherits from AbsOperation and overrides the `inside` method accordingly.
 */
class Union : public AbsOperation
{
public:
    /**
     * @brief Constructs a union operation between two geometries.
     *
     * @param operand1 First input geometry
     * @param operand2 Second input geometry
     */
    Union(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);

    /**
     * @brief Checks whether a point lies inside the union of the operands.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside at least one of the operands
     */
    bool inside(double x, double y) const override;
};

} // namespace implicit
