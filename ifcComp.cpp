#include <iostream>
#define CGAL_USE_BASIC_VIEWER
#include <CGAL/draw_surface_mesh.h>
#include <CGAL/Qt/Basic_viewer_qt.h>
#include "Reader.h"

int main(int argc, char *argv[]) {
    // TODO: Add your code here
    std::cout << "program, init!" << std::endl;
    Mesh  mesh= ReadMesh("data/chair.obj"); 

    CGAL::draw(mesh);
    std::cout << "program, end!" << std::endl;
    return 0;
}
