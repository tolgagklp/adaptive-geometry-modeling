/**
 * @file quadtree.cpp
 * @brief Implements core functions and data structures for adaptive quadtree partitioning.
 *
 * Includes recursive spatial subdivision of 2D domains, intersection tests with implicit geometries,
 * and VTK output generation for visualization.
 */

#include "quadtree.h"
#include "quadtree_helper.h"
#include "AbsImplicitGeometry.hpp"

#include <fstream>
#include <iostream>

namespace implicit {
namespace detail {

/**
 * @brief Subdivides a rectangular cell into four equally sized sub-cells.
 */
std::array<Cell2D, 4> subdivideCell(Cell2D cell)
{
    double xmin = cell[0][0], xmax = cell[0][1];
    double ymin = cell[1][0], ymax = cell[1][1];

    double xmid = 0.5 * (xmin + xmax);
    double ymid = 0.5 * (ymin + ymax);

    Bounds x0{ xmin, xmid }, x1{ xmid, xmax };
    Bounds y0{ ymin, ymid }, y1{ ymid, ymax };

    Cell2D c0{ x0, y0 }, c1{ x0, y1 }, c2{ x1, y0 }, c3{ x1, y1 };

    return { c0, c1, c2, c3 };
}

/**
 * @brief Checks if the cell intersects the boundary of the implicit geometry.
 *
 * Samples `numberOfSeedPoints` along each axis and counts interior hits.
 * Returns true if some points are inside and some are outside.
 */
bool isCutByBoundary(Cell2D cell,
                     const AbsImplicitGeometry &geometry,
                     int numberOfSeedPoints)
{
    double xmin = cell[0][0], xmax = cell[0][1];
    double ymin = cell[1][0], ymax = cell[1][1];

    int count = 0;
    for (int i = 0; i < numberOfSeedPoints; ++i)
    {
        double x = i / (numberOfSeedPoints - 1.0) * (xmax - xmin) + xmin;
        for (int j = 0; j < numberOfSeedPoints; ++j)
        {
            double y = j / (numberOfSeedPoints - 1.0) * (ymax - ymin) + ymin;
            count += geometry.inside(x, y);
        }
    }

    return count != 0 && count != numberOfSeedPoints * numberOfSeedPoints;
}

/**
 * @brief Writes all leaf cells and their levels to a VTK file for visualization.
 */
void writeCellsToVtkFile(const CellsAndLevels &data, const std::string &filename)
{
    const auto &cells = data.first;
    const auto &levels = data.second;
    size_t numberOfCells = cells.size();

    std::ofstream outfile(filename);
    if (!outfile.is_open()) return;

    outfile << "# vtk DataFile Version 4.2\n";
    outfile << "Adaptive Quadtree\n";
    outfile << "ASCII\n";
    outfile << "DATASET UNSTRUCTURED_GRID\n";

    outfile << "POINTS " << 4 * numberOfCells << " double\n";
    for (const auto &cell : cells)
    {
        double x0 = cell[0][0], x1 = cell[0][1];
        double y0 = cell[1][0], y1 = cell[1][1];
        outfile << x0 << " " << y0 << " 0\n";
        outfile << x1 << " " << y0 << " 0\n";
        outfile << x1 << " " << y1 << " 0\n";
        outfile << x0 << " " << y1 << " 0\n";
    }

    outfile << "CELLS " << numberOfCells << " " << 5 * numberOfCells << "\n";
    for (size_t i = 0; i < numberOfCells * 4; i += 4)
        outfile << "4 " << i << " " << i + 1 << " " << i + 2 << " " << i + 3 << "\n";

    outfile << "CELL_TYPES " << numberOfCells << "\n";
    for (size_t i = 0; i < numberOfCells; ++i)
        outfile << "9\n"; // VTK_QUAD

    outfile << "CELL_DATA " << numberOfCells << "\n";
    outfile << "SCALARS depth double\nLOOKUP_TABLE default\n";
    for (const auto &lvl : levels)
        outfile << lvl << "\n";

    outfile.close();
}

/**
 * @brief Constructor for a quadtree node at a given level and cell.
 */
QuadTreeNode::QuadTreeNode(Cell2D cell, int level)
        : cell_(cell), level_(level)
{ }

/**
 * @brief Recursively partitions the node based on geometry boundary interaction.
 */
void QuadTreeNode::partition(const AbsImplicitGeometry &geometry, int maxDepth)
{
    int numberOfSeedPoints = 7;

    if (level_ < maxDepth &&
        isCutByBoundary(cell_, geometry, numberOfSeedPoints))
    {
        auto subCells = subdivideCell(cell_);
        children_.reserve(4);

        for (const auto &sub : subCells)
        {
            children_.emplace_back(sub, level_ + 1);
            children_.back().partition(geometry, maxDepth);
        }
    }
}

/**
 * @brief Returns all leaf cells and their levels from this node and its children.
 */
CellsAndLevels QuadTreeNode::getLeafCells() const
{
    CellsAndLevels data;
    getLeafCellsRecursive(data);
    return data;
}

/**
 * @brief Recursive helper to collect leaf cells.
 */
void QuadTreeNode::getLeafCellsRecursive(CellsAndLevels &data) const
{
    if (children_.empty())
    {
        data.first.push_back(cell_);
        data.second.push_back(level_);
    }
    else
    {
        for (const auto &child : children_)
            child.getLeafCellsRecursive(data);
    }
}

} // namespace implicit::detail

/**
 * @brief Top-level function to generate a quadtree and write it to a VTK file.
 */
void generateQuadTree(const AbsImplicitGeometry &geometry,
                      Cell2D boundingBox,
                      int maxDepth,
                      const std::string &filename)
{
    detail::QuadTreeNode rootNode(boundingBox, 0);
    rootNode.partition(geometry, maxDepth);
    auto leaves = rootNode.getLeafCells();
    detail::writeCellsToVtkFile(leaves, filename);
}

} // namespace implicit
