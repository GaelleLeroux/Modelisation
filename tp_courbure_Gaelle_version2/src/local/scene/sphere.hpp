#include "../../lib/mesh/mesh_parametric.hpp"
#include <cmath>

#ifndef SPHERE_HPP
#define SPHERE_HPP

class sphere {
    public :
    sphere();

    cpe::mesh_parametric& create(cpe::mesh_parametric& surface);


    private :
    int const Nu=200;
    int const Nv=200;
    float const u_min = -M_PI;
    float const u_max = M_PI;
    float const v_min = -M_PI/2;
    float const v_max = M_PI/2;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
    float const b = 1;

    float const a = 0.1;

};

#endif