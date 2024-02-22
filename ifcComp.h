#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/IO/OBJ.h>


#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;


typedef Polyhedron::HalfedgeDS HalfedgeDS;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;