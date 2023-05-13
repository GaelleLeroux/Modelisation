#include "../../lib/mesh/mesh_parametric.hpp"
#include <cmath>

#ifndef CYLINDRIQUE_HPP
#define CYLINDRIQUE_HPP

class cylindrique {
    public :
    cylindrique();

    cpe::mesh_parametric& create(cpe::mesh_parametric& surface);


    private :
    int const Nu=200;
    int const Nv=200;
    float const u_min = 0.0f;
    float const u_max = 2.0f*M_PI;
    float const v_min = 0.0f;
    float const v_max = 2.0f;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
    float const b = 1;

    float const a = 0.1;

};

#endif