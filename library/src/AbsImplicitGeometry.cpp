/**
 * @file AbsImplicitGeometry.cpp
 * @brief Implementation of the abstract base class for implicit geometries.
 */

#include "AbsImplicitGeometry.hpp"

namespace implicit
{

/**
 * @brief Virtual destructor for AbsImplicitGeometry.
 * 
 * Required to ensure proper cleanup of derived classes when deleted through a base pointer.
 */
AbsImplicitGeometry::~AbsImplicitGeometry()
{ }

} // namespace implicit
