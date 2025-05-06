#pragma once

/**
 * @file quadtree_helper.h
 * @brief Provides internal quadtree algorithms and data structures for recursive spatial partitioning.
 *
 * Includes the definition of QuadTreeNode and utility functions such as cell subdivision
 * and boundary intersection checking. Designed for use with implicit geometries.
 */

#include "quadtree.h"
#include <vector>
#include <tuple>

namespace implicit::detail
{

/// A pair of quadtree leaf cells and their corresponding refinement levels
using CellsAndLevels = std::pair<std::vector<Cell2D>, std::vector<unsigned int>>;

/**
 * @brief Subdivides a 2D rectangular cell into four quadrants.
 *
 * @param cell Input cell to subdivide
 * @return An array of 4 sub-cells (top-left, top-right, bottom-left, bottom-right)
 */
std::array<Cell2D, 4> subdivideCell(Cell2D cell);

/**
 * @brief Determines whether the given cell intersects the boundary of an implicit geometry.
 *
 * Uses a number of seed points to probe inside the cell and detect boundary crossing.
 *
 * @param cell Cell to check
 * @param geometry Implicit geometry for boundary check
 * @param numberOfSeedPoints Number of sample points along each axis
 * @return true if the boundary cuts through the cell, false otherwise
 */
bool isCutByBoundary(Cell2D cell,
                     const AbsImplicitGeometry &geometry,
                     int numberOfSeedPoints);

/**
 * @class QuadTreeNode
 * @brief Node in a quadtree representing a rectangular cell and its potential children.
 *
 * Each node stores its level in the tree and subdivides recursively based on interaction with geometry.
 * Leaf nodes represent spatial regions for final output.
 */
class QuadTreeNode
{
public:
    /**
     * @brief Constructs a quadtree node with a given cell and depth level.
     *
     * @param cell Bounding box of the node
     * @param level Current level in the quadtree hierarchy
     */
    QuadTreeNode(Cell2D cell, int level);

    /**
     * @brief Recursively partitions the node based on geometry boundary until max depth.
     *
     * @param geometry Implicit geometry used for boundary detection
     * @param maxDepth Maximum allowed subdivision depth
     */
    void partition(const AbsImplicitGeometry &geometry, int maxDepth);

    /**
     * @brief Retrieves all leaf cells (i.e., non-subdivided terminal nodes).
     *
     * @return A pair of cell data and their corresponding levels
     */
    CellsAndLevels getLeafCells() const;

private:
    /**
     * @brief Helper function for recursively collecting leaf cells.
     *
     * @param data Reference to output container for cells and levels
     */
    void getLeafCellsRecursive(CellsAndLevels &data) const;

    std::vector<QuadTreeNode> children_;  ///< Child nodes (empty if leaf)
    Cell2D cell_;                         ///< Bounding box of the node
    int level_;                           ///< Level of this node in the tree
};

} // namespace implicit::detail
