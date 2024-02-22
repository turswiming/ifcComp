#include "Reader.h"
#include <CGAL/IO/OBJ.h>

Polyhedron ReadMesh(std::string filePath) {
    Polyhedron mesh;

    if (!CGAL::IO::read_OBJ(CGAL::data_file_path("data/chair.obj"), mesh) || mesh.empty() || !CGAL::is_triangle_mesh(mesh))
    {std::cerr << "Error reading file " << filePath << std::endl;
        throw std::runtime_error("Error reading file");
    }
    return mesh;
}