#include "Reader.h"

Mesh ReadMesh(std::string filePath) {
    Mesh mesh;
    std::vector<Point> points;
    std::vector<std::vector<std::size_t>> polygons;

    if(!CGAL::IO::read_OBJ(filePath, points, polygons)) {
        std::cerr << "Error reading file " << filePath << std::endl;
        throw std::runtime_error("Error reading file");
    }
    //convert to mesh
    for(auto p : points) {
        mesh.add_vertex(p);
    }
    for(auto poly : polygons) {
        mesh.add_face(Mesh::Vertex_index(poly[0]), Mesh::Vertex_index(poly[1]), Mesh::Vertex_index(poly[2]));
    }
    return mesh;
}