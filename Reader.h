#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <iostream>
#include <vector>
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Normal;
typedef CGAL::Surface_mesh<Point> Mesh;
Mesh ReadMesh(std::string filePath);