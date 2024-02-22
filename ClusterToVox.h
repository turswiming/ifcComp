//
// Created by User on 2024/2/22.
//

#ifndef IFCCOMP_CLUSTERTOVOX_H
#define IFCCOMP_CLUSTERTOVOX_H

#include "Eigen/Core"
#include "ifcComp.h"

class ClusterToVox {
public:
    void clusterToVox();
    Polyhedron cluster(const Polyhedron& mesh, double resolution);
    void GenerateVoxel(Eigen::Vector3i v, double resolution, Polyhedron &result);

};



#endif //IFCCOMP_CLUSTERTOVOX_H
