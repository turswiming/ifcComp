//
// Created by User on 2024/2/22.
//

#include "ClusterToVox.h"
#include "ifcComp.h"
template <class HDS>
class Build_cube : public CGAL::Modifier_base<HDS>
{
public:
    Build_cube(Eigen::Vector3i position,double resolution) {
        this->position = position;
        this->resolution = resolution;
    }
    void operator()(HDS &hds)
    {
        bool debug = false;
        // Postcondition: hds is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
        B.begin_surface(8, 2, 16);//vertices, facets, halfedges
        typedef typename HDS::Vertex Vertex;
        typedef typename Vertex::Point Point;
        //create a box using resolution as size and position
        Eigen::Vector3d minBound(
            (position.x()-0.5)*resolution,
            (position.y()-0.5)*resolution,
            (position.z()-0.5)*resolution);
        Eigen::Vector3d maxBound(
            (position.x()+0.5)*resolution,
            (position.y()+0.5)*resolution,
            (position.z()+0.5)*resolution);

        for (size_t i = 0; i < 8; i++)
        {
            B.add_vertex(Point(
                (i & 1) ? maxBound.x() : minBound.x(),
                (i & 2) ? maxBound.y() : minBound.y(),
                (i & 4) ? maxBound.z() : minBound.z()));
                if (debug)
                {
                    std::cout << "vertex: " << i << " " 
                    << ((i & 1) ? 1:0) << " " 
                    << ((i & 2) ? 1:0) << " " 
                    << ((i & 4) ? 1:0) << std::endl;
                }
                
                
        }
        /*
            6--------7
        4--------5
        
            2--------3
        0--------1
        */
        //clockwise
        //lower
        B.begin_facet();
        B.add_vertex_to_facet(0);
        B.add_vertex_to_facet(1);
        B.add_vertex_to_facet(3);
        B.add_vertex_to_facet(2);
        B.end_facet();
        //upper
        B.begin_facet();
        B.add_vertex_to_facet(4);
        B.add_vertex_to_facet(6);
        B.add_vertex_to_facet(7);
        B.add_vertex_to_facet(5);
        B.end_facet();
        //front
        B.begin_facet();
        B.add_vertex_to_facet(0);
        B.add_vertex_to_facet(4);
        B.add_vertex_to_facet(5);
        B.add_vertex_to_facet(1);
        B.end_facet();
        //back
        B.begin_facet();
        B.add_vertex_to_facet(3);
        B.add_vertex_to_facet(7);
        B.add_vertex_to_facet(6);
        B.add_vertex_to_facet(2);
        B.end_facet();
        //left
        B.begin_facet();
        B.add_vertex_to_facet(2);
        B.add_vertex_to_facet(6);
        B.add_vertex_to_facet(4);
        B.add_vertex_to_facet(0);
        B.end_facet();
        //right
        B.begin_facet();
        B.add_vertex_to_facet(1);
        B.add_vertex_to_facet(5);
        B.add_vertex_to_facet(7);
        B.add_vertex_to_facet(3);
        B.end_facet();

        B.end_surface();
    }
private:
    Eigen::Vector3i position;
    double resolution;
};
template <typename T>
struct hash_eigen {
    std::size_t operator()(T const& matrix) const {
        size_t hash_seed = 0;
        for (int i = 0; i < (int)matrix.size(); i++) {
            auto elem = *(matrix.data() + i);
            hash_seed ^= std::hash<typename T::Scalar>()(elem) + 0x9e3779b9 +
                         (hash_seed << 6) + (hash_seed >> 2);
        }
        return hash_seed;
    }
};
void ClusterToVox::clusterToVox()
{
}
Polyhedron ClusterToVox::cluster(const Polyhedron &mesh, double resolution)
{
    double scale = 1.0f / resolution;
    auto poly = mesh;
    
    std::vector<Eigen::Vector3d> points;
    auto f = poly.facets_begin();
    
    // do {
        
    //     auto v = f->facet_begin();
    //     std::queue<Eigen::Vector3d> fvertices;
    //     do
    //     {
    //     } while (v != f.vertices_end());
        
    //     //get the distance between the two points
    //     double distance = CGAL::sqrt(CGAL::squared_distance(startPoint, endPoint));
    //     auto diff = endPoint - startPoint;
    //     auto step = Normalize(diff)*resolution;
    //     for (double i = 0; i < distance; i += resolution)
    //     {
    //         points.push_back(startPoint + diff * i * resolution);
    //     }
    // } while (++f != poly.facets_end());


    std::unordered_set<Eigen::Vector3i,hash_eigen<Eigen::Vector3i>> clusters;
    for (const auto &p : poly.points())
    {
        Eigen::Vector3i v;

        v << static_cast<int>(floor(p.x() * scale)), static_cast<int>(floor(p.y() * scale)), static_cast<int>(floor(p.z() * scale));
        if (clusters.find(v) == clusters.end())
        {
            clusters.insert(v);
        }
    }
    Polyhedron result;
    //build a tree, connect the points in the clusters if the distance is less than 1
    //for each cluster, find the nearest cluster, and connect them
    while (clusters.size() > 0)
    {
        Eigen::Vector3i v =*clusters.begin();
        clusters.erase(clusters.begin());
        GenerateVoxel(v, resolution, result);
    }
    


    return result;
}

void ClusterToVox::GenerateVoxel(Eigen::Vector3i v, double resolution, Polyhedron &result)
{
    //build a cube
    Build_cube<HalfedgeDS> cube(v,resolution);
    result.delegate(cube);
}

template <class HDS>
class Remove_triangle : public CGAL::Modifier_base<HDS>
{
public:
    Remove_triangle(Eigen::Vector3i posi,double resolution) {

    }
    void operator()(HDS &hds)
    {
        // Postcondition: hds is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);
        B.begin_surface(3, 1, 6);
        typedef typename HDS::Vertex Vertex;
        typedef typename Vertex::Point Point;
        B.add_vertex(Point(0, 0, 0));
        B.add_vertex(Point(1, 0, 0));
        B.add_vertex(Point(0, 1, 0));
        B.begin_facet();
        B.add_vertex_to_facet(0);
        B.add_vertex_to_facet(1);
        B.add_vertex_to_facet(2);
        B.end_facet();
        B.end_surface();
    }
};