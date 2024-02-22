//
// Created by User on 2024/2/22.
//

#ifndef IFCCOMP_CLUSTERTOVOX_H
#define IFCCOMP_CLUSTERTOVOX_H

template <typename Mesh>
class ClusterToVox {
public:
    void clusterToVox();
    Mesh clusterToVox(const Mesh& mesh, double resolution);
};




#endif //IFCCOMP_CLUSTERTOVOX_H
