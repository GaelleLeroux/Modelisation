#include "cylindrique.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"
using namespace cpe;

vec2 build_courbure_cylindrique(const float& u,const float&  v,const float&  r)
{
    mat2 Is(dot(vec3(-r*sin(u),r*cos(u),0),vec3(-r*sin(u),r*cos(u),0)), 
            dot(vec3(-r*sin(u),r*cos(u),0),vec3(0,0,1)), 
            dot(vec3(-r*sin(u),r*cos(u),0),vec3(0,0,1)),
            dot(vec3(0,0,1),vec3(0,0,1)));
            
    vec3 n = normalized(cross(vec3(-r*sin(u),r*cos(u),0),vec3(0,0,1)))  ;

    mat2 IIs(dot(vec3(-r*cos(u),-r*sin(u),0),n), 
            dot(vec3(0,0,0),n), 
            dot(vec3(0,0,0),n),
            dot(vec3(0,0,0),n));

    mat2 Ws = -IIs*inverse(Is);

    auto lambda = eigenvalue(Ws) ;

    return lambda;

}

cylindrique::cylindrique(){};

mesh_parametric& cylindrique::create(mesh_parametric& surface){
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

            float const x = r*cos(u);
            float const y = r*sin(u);
            float const z = v; 
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
            
            //vec2 lambda = build_courbure_cylindrique_discrete(ku,kv,r,Nu,Nv,surface);
            vec2 lambda = build_courbure_cylindrique(u,v,r);

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
            vec3 couleur;
            if ((std::round((max_c-min_c)*100)/100) != 0){
                couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
            }
            else {
                couleur = colormap(0);
            }
            
            surface.color(ku,kv) = couleur;
        }
    }

    return surface;
}


