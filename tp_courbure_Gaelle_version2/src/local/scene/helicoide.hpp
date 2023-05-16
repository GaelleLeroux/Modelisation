#include "../../lib/mesh/mesh_parametric.hpp"
#include <cmath>

#ifndef HELICOIDE_HPP
#define HELICOIDE_HPP

class helicoide {
    public :
    helicoide();

    cpe::mesh_parametric& create(cpe::mesh_parametric& surface);

    cpe::vec3 du(const float& u,const float&  v,const float&  r);
    cpe::vec3 dv(const float& u,const float&  v,const float&  r);
    cpe::vec3 du2(const float& u,const float&  v,const float&  r);
    cpe::vec3 dv2(const float& u,const float&  v,const float&  r);
    cpe::vec3 dudv(const float& u,const float&  v,const float&  r);


    private :
    int const Nu=200;
    int const Nv=200;
    float const u_min = 0.0f;
    float const u_max = 1.0f;
    float const v_min = -2.0f;
    float const v_max = 2.0f;
    
    float const h = 2;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
    

};

#endif