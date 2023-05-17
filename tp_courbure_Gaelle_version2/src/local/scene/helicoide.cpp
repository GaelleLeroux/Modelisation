#include "helicoide.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"
#include "methode.hpp"

using namespace cpe;

vec3 helicoide::du(const float& u,const float&  v,const float&  r){
    return vec3(cos(v),sin(v),0);
}

vec3 helicoide::dv(const float& u,const float&  v,const float&  r){
    return vec3(-u*sin(v),u*cos(v),h);
}

vec3 helicoide::du2(const float& u,const float&  v,const float&  r){
    return vec3(0,0,0);
}

vec3 helicoide::dv2(const float& u,const float&  v,const float&  r){
    return vec3(-u*cos(v),-u*sin(v),0);
}

vec3 helicoide::dudv(const float& u,const float&  v,const float&  r){
    return vec3(-sin(v),cos(v),0);
}


vec2 build_courbure_helicoide(const float& u,const float&  v,const float&  r)
{
    // Calcul de la métrique de l'hélicoïde
    mat2 Is(
        dot(vec3(1 + pow(r, 2) * pow(v, 2), 0, 2 * r * v), vec3(1 + pow(r, 2), 0, 0)),
        dot(vec3(1 + pow(r, 2) * pow(v, 2), 0, 2 * r * v), vec3(0, 1, 0)),
        dot(vec3(1 + pow(r, 2), 0, 0), vec3(0, 1, 0)),
        dot(vec3(pow(r, 2), 0, 0), vec3(pow(v, 2), 0, 0))
    );

    // Calcul de la normale à l'hélicoïde
    vec3 n = normalized(cross(
        vec3(-r * cos(u), -r * sin(u), v),
        vec3(0, 0, 2)
    ));

    // Calcul du tenseur de courbure
    mat2 IIs(
        dot(vec3(-r * sin(u), r * cos(u), 0), n),
        dot(vec3(0, 0, 0), n),
        dot(vec3(0, 0, 0), n),
        dot(vec3(0, 0, 0), n)
    );

    // Calcul du tenseur de Weingarten
    mat2 Ws = -IIs * inverse(Is);

    // Calcul des valeurs propres du tenseur de Weingarten
    auto lambda = eigenvalue(Ws);

    return lambda;
}


helicoide::helicoide(){};

cpe::mesh_parametric& helicoide::create(cpe::mesh_parametric& surface,bool Discret){
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

            float const x = u*cos(v);
            float const y = u*sin(v);
            float const z = h*v;   
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
           
            liste_lambda[ku*Nv+kv] = lambda2;

            // min_c = min(min_c,lambda1);
            // max_c = max(max_c,lambda1);

            min_c = min(min_c,lambda2);
            max_c = max(max_c,lambda2);

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
                couleur = colormap_supernova((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                // couleur = colormap_hsv_matlab((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
            }
            else {
                couleur = colormap_supernova(0);
                // couleur = colormap_hsv_matlab(0);
            }
            
            surface.color(ku,kv) = couleur;
        }
    }

    return surface;
}

