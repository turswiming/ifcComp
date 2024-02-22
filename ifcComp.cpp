
#include <iostream>
#include <fstream>
#include <CGAL/draw_polyhedron.h>
#include <CGAL/Polygon_mesh_processing/bbox.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/alpha_wrap_3.h>
#include <CGAL/Real_timer.h>


#include "ifcComp.h"
#include "Reader.h"
#include "ClusterToVox.h"

// A modifier creating a triangle with the incremental builder.

int main()
{
    // create and read Polyhedron
    Polyhedron mesh = ReadMesh("data/chair.obj");
    // create a property-map
    typedef std::map<face_descriptor, double> Face_double_map;
    Face_double_map internal_map;
    boost::associative_property_map<Face_double_map> sdf_property_map(internal_map);
    //get the boundary of the mesh
    CGAL::Bbox_3 bbox = CGAL::Polygon_mesh_processing::bbox(mesh);
    std::cout << "bbox: " << bbox << std::endl;
    double  diffX = (bbox.xmax() - bbox.xmin())/2;
    double  diffY = (bbox.ymax() - bbox.ymin())/2;
    double  diffZ = (bbox.zmax() - bbox.zmin())/2;
    for (auto & p:mesh.points()) {
        p = p - CGAL::Vector_3<Kernel>(bbox.xmin() + diffX, bbox.ymin() + diffY, bbox.zmin() + diffZ);
    }
    CGAL::draw(mesh);
    ClusterToVox(mesh, 0.1);

    return EXIT_SUCCESS;
}