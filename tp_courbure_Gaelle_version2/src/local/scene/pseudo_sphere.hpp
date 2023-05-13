#include "../../lib/mesh/mesh_parametric.hpp"
#include <cmath>

#ifndef PSEUDO_SPHERE_HPP
#define PSEUDO_SPHERE_HPP

class pseudo_sphere {
    public :
    pseudo_sphere();

    cpe::mesh_parametric& create(cpe::mesh_parametric& surface);


    private :
    int const Nu=200;
    int const Nv=200;
    float const u_min = -3.0f;
    float const u_max = 3.0f;
    float const v_min = 0.0f;
    float const v_max = 2.0f*M_PI;
    
    float const a = 0.5;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
    

};

#endif