#include "cylindrique.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"
using namespace cpe;

vec2 build_courbure_catenoide(const float& u,const float&  v,const float&  r)
{
    
    // Calcul du tenseur métrique
    mat2 Is(dot(cosh(v)*cosh(v)-r*r*sin(u)*sin(u)*sinh(v)*sinh(v), 0.0f, -r*r*cos(u)*sin(u)*sinh(v)*sinh(v), 1.0f), 
            dot(0.0f, r*r, 0.0f, 1.0f), 
            dot(-r*r*cos(u)*sin(u)*sinh(v)*sinh(v), 0.0f, r*r*sin(u)*sin(u)*sinh(v)*sinh(v)-cosh(v)*cosh(v), 1.0f),
            dot(1.0f, 1.0f, 1.0f, 0.0f));
            
    // Calcul du vecteur normal
    vec3 n = normalized(cross(vec3(-r*sinh(v)*cos(u), -r*sinh(v)*sin(u), r*cosh(v))));

    // Calcul du tenseur de courbure
    mat2 IIs(dot(-r*r*sinh(v)*cosh(v)*cos(u)*sin(u), -r*r*cosh(v)*sinh(v)*sin(u), 0.0f, 0.0f), 
             dot(-r*r*cosh(v)*sinh(v)*cos(u), r*r*cosh(v)*sinh(v)*cos(u), 0.0f, 0.0f),
             dot(0.0f, 0.0f, -r*r*sinh(v)*cosh(v)*cos(u)*sin(u), -r*r*cosh(v)*sinh(v)*sin(u)),
             dot(0.0f, 0.0f, -r*r*cosh(v)*sinh(v)*sin(u), r*r*sinh(v)*cosh(v)*sin(u)));
    
    // Calcul des courbures principales
    mat2 Ws = -IIs*inverse(Is);
    auto lambda = eigenvalue(Ws);

    return lambda;
}


catenoide::catenoide(){};

cpe::mesh_parametric& catenoide::create(cpe::mesh_parametric& surface){
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
            
            cpe::vec2 lambda = build_courbure_cylindrique_discrete(ku,kv,r,Nu,Nv,surface);

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
                couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                //std::cout<<(liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c)<<std::endl;
            }
            else {
                couleur = colormap(0);
            }
            
            surface.color(ku,kv) = couleur;
        }
    }

    return surface;
}

