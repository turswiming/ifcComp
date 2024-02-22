#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>
#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include "ifcComp.h"
Polyhedron ReadMesh(std::string filePath);