#pragma once

/**
 * @file Intersection.hpp
 * @brief Defines the CSG operation for intersection between two implicit geometries.
 */

#include "AbsOperation.hpp"

namespace implicit
{

/**
 * @class Intersection
 * @brief Represents the intersection of two implicit geometries.
 *
 * A point is considered inside the intersection if it is inside **both** operand geometries.
 * This class inherits from AbsOperation and overrides the `inside` method accordingly.
 */
class Intersection : public AbsOperation
{
public:
    /**
     * @brief Constructs an intersection operation between two geometries.
     *
     * @param operand1 First input geometry
     * @param operand2 Second input geometry
     */
    Intersection(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);

    /**
     * @brief Checks whether a point lies inside the intersection of both operands.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside both operands, false otherwise
     */
    bool inside(double x, double y) const override;
};

} // namespace implicit
