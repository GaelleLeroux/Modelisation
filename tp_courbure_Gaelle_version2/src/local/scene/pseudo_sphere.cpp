#include "pseudo_sphere.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"

using namespace cpe;

vec3 pseudo_sphere::du(const float& u,const float&  v,const float&  r){
    return vec3(-a*cos(v)*sinh(u)/(cosh(u)*cosh(u)),-a*sin(v)*sinh(u)/(cosh(u)*cosh(u)),a*(1-1/(cosh(u)*cosh(u))));
}

vec3 pseudo_sphere::dv(const float& u,const float&  v,const float&  r){
    return vec3(-a*sin(v)/cosh(u),a*cos(v)/cosh(u),0);
}

vec3 pseudo_sphere::du2(const float& u,const float&  v,const float&  r){
    return vec3((-a*cos(v)*tanh(u)/cosh(u))-(2*a*cos(v)*1/(cosh(u)*cosh(u))),(-a*sin(v)*tanh(u)/cosh(u))-(2*a*sin(v)*1/(cosh(u)*cosh(u))),-2*a*tanh(v)/(cosh(u)*cosh(u)));
}

vec3 pseudo_sphere::dv2(const float& u,const float&  v,const float&  r){
    return vec3(-a*cos(v)/cosh(u),-a*sin(v)/cosh(u),0);
}

vec3 pseudo_sphere::dudv(const float& u,const float&  v,const float&  r){
    return vec3(a*sin(v)*sinh(u)/(cosh(u)*cosh(u)),-a*cos(v)*sinh(u)/(cosh(u)*cosh(u)),0);
}


pseudo_sphere::pseudo_sphere(){};

cpe::mesh_parametric& pseudo_sphere::create(cpe::mesh_parametric& surface){
    surface.set_plane_xy_unit(Nu,Nv);
    liste_lambda.resize(Nu*Nv);

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            float const u_n = static_cast<float>(ku)/(Nu-1);
            float const v_n = static_cast<float>(kv)/(Nv-1);

            float const u = u_min + u_n * (u_max-u_min);
            float const v = v_min + v_n * (v_max-v_min);

            float const x = a*cos(v)/cosh(u);
            float const y = a*sin(v)/cosh(u);
            float const z = a*(u-tanh(u));   
            surface.vertex(ku,kv) = {x,y,z};
        };
    };

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            float const u_n = static_cast<float>(ku)/(Nu-1);
            float const v_n = static_cast<float>(kv)/(Nv-1);

            float const u = u_min + u_n * (u_max-u_min);
            float const v = v_min + v_n * (v_max-v_min);
            
            vec2 lambda = build_courbure_discrete(ku,kv,r,Nu,Nv,surface);
            //vec2 lambda = build_courbure_analytique(du(u,v,r),dv(u,v,r),du2(u,v,r),dv2(u,v,r),dudv(u,v,r));

            float Ks = lambda.x()*lambda.y();
            float Hs = 0.5* (lambda.x()+lambda.y());
           
            liste_lambda[ku*Nv+kv] = Ks;
            min_c = min(min_c,Ks);
            max_c = max(max_c,Ks);

            // min_c = min(min_c,Hs);
            // max_c = max(max_c,Hs);

        }
    }

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            cpe::vec3 couleur;
            if ((std::round((max_c-min_c)*100)/100) != 0){
                couleur = colormap_hsv_matlab((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                // couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                //std::cout<<(liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c)<<std::endl;
            }
            else {
                couleur = colormap_hsv_matlab(0);
                // couleur = colormap(0);
            }
            
            surface.color(ku,kv) = couleur;
        }
    }

    return surface;
}

