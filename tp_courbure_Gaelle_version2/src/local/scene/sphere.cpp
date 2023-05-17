#include "sphere.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"
#include <iostream>

using namespace cpe;

vec3 du(const float& u,const float&  v,const float&  r){
    return vec3(-r*sin(u)*cos(v),r*cos(u)*cos(v),0);
}

vec3 dv(const float& u,const float&  v,const float&  r){
    return vec3(-r*cos(u)*sin(v),-r*sin(u)*sin(v),r*cos(v));
}

vec3 du2(const float& u,const float&  v,const float&  r){
    return vec3(-r*cos(u)*cos(v),-r*sin(u)*cos(v),0);
}

vec3 dv2(const float& u,const float&  v,const float&  r){
    return vec3(-r*cos(u)*cos(v),-r*sin(u)*cos(v),-r*sin(v));
}

vec3 dudv(const float& u,const float&  v,const float&  r){
    return vec3(r*sin(u)*sin(v),-r*cos(u)*sin(v),0);
}


sphere::sphere(){};

mesh_parametric& sphere::create(mesh_parametric& surface,bool Discret){
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

            float const x = r*cos(u)*cos(v);
            float const y = r*sin(u)*cos(v);
            float const z = r*sin(v); 
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
            
            vec2 lambda;
            if (Discret){
                lambda = build_courbure_discrete(ku,kv,r,Nu,Nv,surface);
            }
            else{
                lambda = build_courbure_analytique(du(u,v,r),dv(u,v,r),du2(u,v,r),dv2(u,v,r),dudv(u,v,r));
            }

            float Ks = std::round(lambda.x())*std::round(lambda.y());
            float Hs = 0.5* (lambda.x()+lambda.y());

            // std::cout<<lambda.x()<<"  "<<lambda.y()<<std::endl;
           
            liste_lambda[ku*Nv+kv] = Hs;
            // min_c = min(min_c,Ks);
            // max_c = max(max_c,Ks);

            if (std::isnan(lambda.y())){
                liste_lambda[ku*Nv+kv] = liste_lambda[ku*Nv+kv-1];
            }

            min_c = min(min_c,Hs);
            max_c = max(max_c,Hs);

        }
    }
    std::cout<<min_c<<std::endl;
    std::cout<<max_c<<std::endl;
    // std::cout<<std::round((max_c-min_c)*100)/100<<std::endl;
    

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            vec3 couleur;
            if ((std::round((max_c-min_c)*100)/100) != 0){
                // couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                couleur = colormap_hsv_matlab((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
            }
            else {
                // couleur = colormap(0);
                couleur = colormap_hsv_matlab(0);
            }
            // std::cout<<couleur<<std::endl;
            surface.color(ku,kv) = couleur;
        }
    }

    return surface;
}



