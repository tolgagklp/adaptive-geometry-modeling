#pragma once

/**
 * @file AbsImplicitGeometry.hpp
 * @brief Defines the abstract base class for all 2D implicit geometries.
 */

namespace implicit
{

/**
 * @class AbsImplicitGeometry
 * @brief Abstract base class for representing implicit 2D geometries.
 *
 * This class defines the interface for all implicit shapes, such as circles and rectangles.
 * Each derived class must implement the `inside` function, which checks whether a given
 * point lies inside the shape.
 */
class AbsImplicitGeometry
{
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~AbsImplicitGeometry();

    /**
     * @brief Checks if the given (x, y) point lies inside the geometry.
     *
     * @param x X-coordinate of the point
     * @param y Y-coordinate of the point
     * @return true if the point is inside the geometry, false otherwise
     */
    virtual bool inside(double x, double y) const = 0;
};

} // namespace implicit
