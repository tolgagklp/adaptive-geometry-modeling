#pragma once

/**
 * @file AbsOperation.hpp
 * @brief Defines an abstract base class for boolean operations on implicit geometries.
 */

#include <memory>
#include "AbsImplicitGeometry.hpp"

namespace implicit
{

/// Convenient alias for shared pointer to an implicit geometry
using ImplicitGeometryPtr = std::shared_ptr<AbsImplicitGeometry>;

/**
 * @class AbsOperation
 * @brief Abstract base class for binary operations (CSG) between two implicit geometries.
 *
 * This class represents a generic boolean operation (such as union, intersection, difference)
 * between two shapes. It stores two operands as shared pointers and is intended to be inherited
 * by specific operation classes.
 */
class AbsOperation : public AbsImplicitGeometry
{
public:
    /**
     * @brief Constructs a binary operation with two operand geometries.
     *
     * @param operand1 First input geometry
     * @param operand2 Second input geometry
     */
    AbsOperation(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);

    /**
     * @brief Virtual destructor.
     */
    virtual ~AbsOperation();

protected:
    /// First operand of the operation
    ImplicitGeometryPtr operand1_;

    /// Second operand of the operation
    ImplicitGeometryPtr operand2_;
};

} // namespace implicit
