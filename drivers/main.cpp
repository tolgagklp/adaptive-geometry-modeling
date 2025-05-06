/**
 * @file main.cpp
 * @brief Entry point for combining implicit geometries and generating a quadtree.
 *
 * Demonstrates the use of basic CSG operations (union, intersection, difference)
 * and adaptive spatial subdivision using a quadtree. Outputs result as VTK.
 */

#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Intersection.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "quadtree.h"

#include <iostream>
#include <chrono>

/**
 * @brief ASCII visualization of the implicit geometry in terminal.
 *
 * Prints a 2D grid with 'X' for points inside the geometry and blank for outside.
 */
void visualize(const implicit::ImplicitGeometryPtr object)
{
    double nx = 70;
    double ny = 40;

    double x1 = -3;
    double y1 = -3;
    double x2 = 3;
    double y2 = 3;

    for (int i = 0; i < ny; ++i)
    {
        for (int j = 0; j < nx; ++j)
        {
            double x = x1 + (x2 - x1) / (nx - 1) * j;
            double y = y1 + (y2 - y1) / (ny - 1) * i;

            if (object->inside(x, y))
                std::cout << "X";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    // Define basic geometries
    auto circle1 = std::make_shared<implicit::Circle>(0.0, 0.0, 1.06);
    auto rectangle1 = std::make_shared<implicit::Rectangle>(-1.0, -1.0, 1.0, 1.0);
    auto intersection = std::make_shared<implicit::Intersection>(circle1, rectangle1);

    auto rectangle2 = std::make_shared<implicit::Rectangle>(-0.1, -1.5, 0.1, 1.5);
    auto union1 = std::make_shared<implicit::Union>(intersection, rectangle2);

    auto circle2 = std::make_shared<implicit::Circle>(0.0, 0.0, 0.65);

    // Final composite geometry using CSG: (circle ∩ rectangle + bar) \ inner circle
    auto geometry = std::make_shared<implicit::Difference>(union1, circle2);

    // Optional: ASCII visualization
    visualize(geometry);

    // Define the bounding box for the quadtree
    implicit::Cell2D boundingBox {
            implicit::Bounds { -1.58, 1.58 },
            implicit::Bounds { -1.58, 1.58 }
    };

    // Generate adaptive quadtree and write to VTK file
    implicit::generateQuadTree(*geometry, boundingBox, 7, "quadtree.vtk");

    // Measure and report execution time
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
