
#include <iostream>
#include <fstream>
#include <CGAL/draw_polyhedron.h>
#include <CGAL/Polygon_mesh_processing/bbox.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/alpha_wrap_3.h>
#include <CGAL/Real_timer.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/boost/graph/IO/polygon_mesh_io.h>

#include "ifcComp.h"
#include "Reader.h"
#include "ClusterToVox.h"

// A modifier creating a triangle with the incremental builder.
Polyhedron alphashape();

void writeMeshToObj(const Polyhedron &mesh, const std::string &filename)
{

    CGAL::IO::write_polygon_mesh(filename, mesh);
    std::cout << "Mesh written to " << filename << std::endl;
}

int main()
{
    // create and read Polyhedron
    Polyhedron wrap = alphashape();
    Stop stop(0.1);
    CGAL::Surface_mesh_simplification::edge_collapse(wrap, stop);
    CGAL::draw(wrap);

    writeMeshToObj(wrap, "output.obj");
    //show file size and compression ratio
    std::ifstream input("output.obj", std::ios::binary);
    std::ifstream input2("data/chair.obj", std::ios::binary);
    std::cout << "output.obj size: " << input.tellg() << std::endl;
    std::cout << "data/chair.obj size: " << input2.tellg() << std::endl;
    std::cout << "compression ratio: " << (double)input.tellg() / input2.tellg() << std::endl;

    return EXIT_SUCCESS;
}
Polyhedron alphashape()
{
    Polyhedron mesh = ReadMesh("data/chair.obj");
    // create a property-map
    typedef std::map<face_descriptor, double> Face_double_map;
    Face_double_map internal_map;
    boost::associative_property_map<Face_double_map> sdf_property_map(internal_map);
    // get the boundary of the mesh
    CGAL::Bbox_3 bbox = CGAL::Polygon_mesh_processing::bbox(mesh);
    std::cout << "bbox: " << bbox << std::endl;
    double diffX = (bbox.xmax() - bbox.xmin()) / 2;
    double diffY = (bbox.ymax() - bbox.ymin()) / 2;
    double diffZ = (bbox.zmax() - bbox.zmin()) / 2;
    for (auto &p : mesh.points())
    {
        p = p - CGAL::Vector_3<Kernel>(bbox.xmin() + diffX, bbox.ymin() + diffY, bbox.zmin() + diffZ);
    }
    CGAL::Bbox_3 bboxNew = CGAL::Polygon_mesh_processing::bbox(mesh);
    const double relative_alpha = 80.;
    const double relative_offset = 600.;
    const double diag_length = std::sqrt(CGAL::square(bboxNew.xmax() - bboxNew.xmin()) +
                                         CGAL::square(bboxNew.ymax() - bboxNew.ymin()) +
                                         CGAL::square(bboxNew.zmax() - bboxNew.zmin()));
    const double alpha = diag_length / relative_alpha;
    const double offset = diag_length / relative_offset;
    std::cout << "alpha: " << alpha << ", offset: " << offset << std::endl;
    Polyhedron wrap;
    CGAL::alpha_wrap_3(mesh, alpha, offset, wrap);
    return wrap;
}