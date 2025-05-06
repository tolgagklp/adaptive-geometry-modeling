/**
 * @file AbsOperation.cpp
 * @brief Implements the base class for boolean operations on implicit geometries.
 */

#include "AbsOperation.hpp"

namespace implicit
{

/**
 * @brief Constructs an abstract binary operation with two operand geometries.
 *
 * Stores shared pointers to both operands. Used as a base class
 * for specific operations like Union, Intersection, and Difference.
 */
AbsOperation::AbsOperation(ImplicitGeometryPtr operand1,
                           ImplicitGeometryPtr operand2)
        : operand1_(operand1), operand2_(operand2)
{ }

/**
 * @brief Virtual destructor to enable proper polymorphic cleanup.
 */
AbsOperation::~AbsOperation()
{ }

} // namespace implicit
