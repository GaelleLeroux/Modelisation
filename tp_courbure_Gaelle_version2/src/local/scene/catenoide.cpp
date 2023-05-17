#include "catenoide.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"
using namespace cpe;


vec3 catenoide::du(const float& u,const float&  v,const float&  r){
    return vec3(a*sinh(u)*cos(v), a*sinh(u)*sin(v), a);
}

vec3 catenoide::dv(const float& u,const float&  v,const float&  r){
    return vec3(-a*cosh(u)*sin(v), a*cosh(u)*cos(v), 0);
}

vec3 catenoide::du2(const float& u,const float&  v,const float&  r){
    return vec3(a*cosh(u)*cos(v), a*cosh(u)*sin(v), 0);
}

vec3 catenoide::dv2(const float& u,const float&  v,const float&  r){
    return vec3(-a*cosh(u)*cos(v), -a*cosh(u)*sin(v), 0);
}

vec3 catenoide::dudv(const float& u,const float&  v,const float&  r){
    return vec3(-a*sinh(u)*sin(v), a*sinh(u)*cos(v), 0);
}


catenoide::catenoide(){};

cpe::mesh_parametric& catenoide::create(cpe::mesh_parametric& surface,bool Discret){
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

            float const x = a*cosh(u)*cos(v);
            float const y = a*cosh(u)*sin(v);
            float const z = a*(u);   
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
            

            float Ks = lambda.x()*lambda.y();
            float Hs = 0.5* (lambda.x()+lambda.y());
            float lambda1 = lambda.x();
            float lambda2 = lambda.y();
           
            liste_lambda[ku*Nv+kv] = Hs;

            // min_c = min(min_c,lambda1);
            // max_c = max(max_c,lambda1);

            // min_c = min(min_c,lambda2);
            // max_c = max(max_c,lambda2);

            // min_c = min(min_c,Ks);
            // max_c = max(max_c,Ks);

            min_c = min(min_c,Hs);
            max_c = max(max_c,Hs);

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

