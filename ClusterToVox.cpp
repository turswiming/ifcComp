//
// Created by User on 2024/2/22.
//

#include "ClusterToVox.h"
#include "ifcComp.h"

template<typename Mesh>
void ClusterToVox<Mesh>::clusterToVox() {

}

template<typename Mesh>
Mesh ClusterToVox<Mesh>::clusterToVox(const Mesh& mesh, double resolution) {
    double scale = 1.0f/resolution;
    auto poly =const_cast<Polyhedron>(mesh);
    std::set<Eigen::Vector3i> clusters;
    for (const auto& p:poly.points()) {
        Eigen::Vector3i v;

        v << floor(p.x()*scale), floor(p.y()*scale), floor(p.z()*scale);
        if (clusters.find(v) == clusters.end()) {
            clusters.insert(v);
        }
    }
}

template <class HDS>
class Build_triangle : public CGAL::Modifier_base<HDS> {
public:
    Build_triangle() {}
    void operator()( HDS& hds) {
        // Postcondition: hds is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface( 3, 1, 6);
        typedef typename HDS::Vertex   Vertex;
        typedef typename Vertex::Point Point;
        B.add_vertex( Point( 0, 0, 0));
        B.add_vertex( Point( 1, 0, 0));
        B.add_vertex( Point( 0, 1, 0));
        B.begin_facet();
        B.add_vertex_to_facet( 0);
        B.add_vertex_to_facet( 1);
        B.add_vertex_to_facet( 2);
        B.end_facet();
        B.end_surface();
    }
};