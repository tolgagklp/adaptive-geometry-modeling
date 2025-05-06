#pragma once

/**
 * @file quadtree.h
 * @brief Provides an interface for generating a quadtree from an implicit geometry.
 *
 * This header defines types and a utility function to create a quadtree structure
 * for spatial subdivision of 2D implicit geometries.
 */

#include <array>
#include <string>

namespace implicit
{

/// Represents a 1D range [min, max]
using Bounds = std::array<double, 2>;

/// Represents a 2D rectangular cell as {x-bounds, y-bounds}
using Cell2D = std::array<Bounds, 2>;

class AbsImplicitGeometry;

/**
 * @brief Generates a quadtree over the given bounding box and geometry.
 *
 * The function performs recursive spatial subdivision up to a given depth and
 * exports the resulting cells as a `.vtk` file for visualization (e.g., with ParaView).
 *
 * @param geometry Implicit geometry used for subdivision criteria
 * @param boundingBox Initial 2D bounding box of the quadtree domain
 * @param maxDepth Maximum subdivision depth (controls resolution)
 * @param filename Output file path (should end with .vtk)
 */
void generateQuadTree(const AbsImplicitGeometry &geometry,
                      Cell2D boundingBox,
                      int maxDepth,
                      const std::string &filename);

} // namespace implicit
