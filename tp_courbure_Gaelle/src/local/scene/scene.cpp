

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"

#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include "../interface/myWidgetGL.hpp"

#include <cmath>

#include <string>
#include <sstream>
#include "../../lib/mesh/mesh_io.hpp"

#include "../../lib/3d/mat2.hpp"
#include "../../lib/3d/vec3.hpp"


using namespace cpe;

float min(float x,float y){
    if (x>y){
        return y;
    }
    else {
        return x;
    }
}

float max(float x,float y){
    if (x>y){
        return x;
    }
    else {
        return y;
    }
}

// colormap qu'on avait choisis de base
vec3 colormap(float x) {
    return vec3(1.0, std::min(std::max(x,0.f),1.f), std::min(std::max(1.f-x,0.f),1.f));
}

// // color map matlab automn
// vec3 colormap(float x) {
//     float g = std::min(std::max(x,0.f),1.f);
//     return vec3(1.0, g, 0.0);
// }

// color map matlab automn
vec3 colormap(float x) {
    float g = min(max(x,0.f),1.f);
    return vec3(1.0, g, 0.0);
}


void scene::build_surface_cylindrique()
{
    int const Nu=200;
    int const Nv=200;
    surface.set_plane_xy_unit(Nu,Nv);

    float const u_min = -2.0f;
    float const u_max = 2.0f;
    float const v_min = 0.0f;
    float const v_max = 5*2.0f*M_PI;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
    liste_lambda.resize(Nu*Nv);
    // float const a = 1;
    float const b = 1;

    float const a = 0.1;

    

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            float const u_n = static_cast<float>(ku)/(Nu-1);
            float const v_n = static_cast<float>(kv)/(Nv-1);

            float const u = u_min + u_n * (u_max-u_min);
            float const v = v_min + v_n * (v_max-v_min);

            // //CYLINDRE
            // // float const x = r*cos(u);
            // // float const y = r*sin(u);
            // // float const z = v;   

            //CHAPEAU
            // float const x = a*cos(u)*cos(u)*cos(u)*cos(v)*cos(v)*cos(v);
            // float const y = b*sin(u)*sin(u)*sin(u)*cos(v)*cos(v)*cos(v);
            // float const z = a*sin(v)*sin(v)*sin(v);   

            //CHIPS
            // float const x = u*cos(v);
            // float const y = u*sin(v);
            // float const z = u*cos(v)*cos(v)*cos(v);  

            // float const x = a*cosh(u+v)*cos(1/tan((u-v)*(M_PI/4)));
            // float const y = a*cosh(u+v)*sin(1/tan((u-v)*(M_PI/4)));
            // float const z = a*(u+v);  

            float const x = a*cosh(u)*cos(v);
            float const y = a*cosh(u)*sin(v);
            float const z = a*(u);  

            // float const x = r*cosh(cosh(u))*cos(v);
            // float const y = r*cosh(cosh(u))*sin(v);
            // float const z = r*(u); 

            // float const x = 0.5*cos(u);
            // float const y = 0.7*cos(v);
            // float const z = 0.5*sin(u)+0.7*sin(v);  

            //CATENOIDE
            // float const x = a*cosh(u+v)*cos(1/tan((M_PI/4)*(u-v)));
            // float const y = a*cosh(u+v)*sin(1/tan((M_PI/4)*(u-v)));
            // float const z = a*(u+v); 

            // float const x = a*cosh(u)*cos(v);
            // float const y = a*cosh(u)*sin(v);
            // float const z = a*(ku); 

            surface.vertex(ku,kv) = {x,y,z};
        }
    }
    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            float const u_n = static_cast<float>(ku)/(Nu-1);
            float const v_n = static_cast<float>(kv)/(Nv-1);

            float const u = u_min + u_n * (u_max-u_min);
            float const v = v_min + v_n * (v_max-v_min);
            

            // vec2 lambda = build_courbure_cylindrique(u,v,r);
            vec2 lambda = build_courbure_cylindrique_discrete(ku,kv,r,Nu,Nv);
            // vec2 lambda = build_courbure_chapeau(u,v,r,a,b);

            float Ks = lambda.x()*lambda.y();
            float Hs = 0.5* (lambda.x()+lambda.y());
           
            liste_lambda[ku*Nv+kv] = Ks;
            min_c = min(min_c,Ks);
            max_c = max(max_c,Ks);

            // min_c = min(min_c,Hs);
            // max_c = max(max_c,Hs);
            // min_c = min(min_c,Hs);
            // max_c = max(max_c,Hs);

        }
    }
    std::cout<<min_c<<std::endl;
    std::cout<<max_c<<std::endl;

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            vec3 couleur;
            if ((std::round((max_c-min_c)*100)/100) != 0){
            if ((std::round((max_c-min_c)*100)/100) != 0){
                couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
                // std::cout<<(liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c)<<std::endl;
            }
            else {
                couleur = colormap(0);
            }
            
            surface.color(ku,kv) = couleur;
        }
    }

}

vec2 scene::build_courbure_cylindrique(const float& u,const float&  v,const float&  r)
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

vec2 scene::build_courbure_chapeau(const float& u,const float&  v,const float&  r, const float& a, const float& b)
{
    mat2 Is(dot(vec3(-3*a*sin(u)*sin(u)*cos(v)*cos(v)*cos(v),3*b*cos(u)*cos(u)*cos(v)*cos(v)*cos(v),0),vec3(-3*a*sin(u)*sin(u)*cos(v)*cos(v)*cos(v),3*b*cos(u)*cos(u)*cos(v)*cos(v)*cos(v),0)), 
            dot(vec3(-3*a*sin(u)*sin(u)*cos(v)*cos(v)*cos(v),3*b*cos(u)*cos(u)*cos(v)*cos(v)*cos(v),0),vec3(-3*a*cos(u)*cos(u)*cos(u)*sin(v)*sin(v),-3*b*sin(u)*sin(u)*sin(u)*sin(v)*sin(v),3*a*cos(v)*cos(v))), 
            dot(vec3(-3*a*sin(u)*sin(u)*cos(v)*cos(v)*cos(v),3*b*cos(u)*cos(u)*cos(v)*cos(v)*cos(v),0),vec3(-3*a*cos(u)*cos(u)*cos(u)*sin(v)*sin(v),-3*b*sin(u)*sin(u)*sin(u)*sin(v)*sin(v),3*a*cos(v)*cos(v))),
            dot(vec3(-3*a*cos(u)*cos(u)*cos(u)*sin(v)*sin(v),-3*b*sin(u)*sin(u)*sin(u)*sin(v)*sin(v),3*a*cos(v)*cos(v)),vec3(-3*a*cos(u)*cos(u)*cos(u)*sin(v)*sin(v),-3*b*sin(u)*sin(u)*sin(u)*sin(v)*sin(v),3*a*cos(v)*cos(v))));
        
    vec3 n = normalized(cross(vec3(-3*a*sin(u)*sin(u)*cos(v)*cos(v)*cos(v),3*b*cos(u)*cos(u)*cos(v)*cos(v)*cos(v),0),vec3(-3*a*cos(u)*cos(u)*cos(u)*sin(v)*sin(v),-3*b*sin(u)*sin(u)*sin(u)*sin(v)*sin(v),3*a*cos(v)*cos(v))))  ;

    mat2 IIs(dot(vec3(-6*a*cos(u)*cos(v)*cos(v)*cos(v),-6*b*sin(u)*cos(v)*cos(v)*cos(v),0),n), 
            dot(vec3(9*a*sin(u)*sin(u)*sin(v)*sin(v),-9*b*cos(u)*cos(u)*sin(v)*sin(v),0),n), 
            dot(vec3(9*a*sin(u)*sin(u)*sin(v)*sin(v),-9*b*cos(u)*cos(u)*sin(v)*sin(v),0),n),
            dot(vec3(-6*a*cos(u)*cos(u)*cos(u)*cos(v),-6*b*sin(u)*sin(u)*sin(u)*cos(v),-6*a*sin(v)),n));

    mat2 Ws = -IIs*inverse(Is);

    auto lambda = eigenvalue(Ws) ;

    return lambda;

}

vec2 scene::build_courbure_cylindrique_discrete(const float& u,const float&  v,const float&  r,const int& Nu, const int& Nv)
{
    if (u!=0 and u!=Nu-1 and v!=0 and v!=Nv-1){
        mat2 Is(dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u+1,v)-surface.vertex(u-1,v))/2), 
                dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2), 
                dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2), 
                dot((surface.vertex(u,v+1)-surface.vertex(u,v-1))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2));

        vec3 n = normalized(cross((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2));

        mat2 IIs(dot((surface.vertex(u+1,v)-2*surface.vertex(u,v)+surface.vertex(u-1,v)),n), 
                dot((surface.vertex(u+1, v+1)-surface.vertex(u+1,v-1)-surface.vertex(u-1,v+1)+surface.vertex(u-1,v-1))/4,n), 
                dot((surface.vertex(u+1, v+1)-surface.vertex(u+1,v-1)-surface.vertex(u-1,v+1)+surface.vertex(u-1,v-1))/4,n), 
                dot((surface.vertex(u,v+1)-2*surface.vertex(u,v)+surface.vertex(u,v-1)),n));

        mat2 Ws = -IIs*inverse(Is);
        auto lambda = eigenvalue(Ws) ;
        return lambda;
    }
    else {
        return vec2{0,0};
    }

}


void scene::load_scene()
{
    load_common_data();


    build_surface_cylindrique();


    surface.fill_normal();
    surface.fill_empty_field_by_default();

    surface_opengl.fill_vbo(surface);

}

void scene::draw_scene()
{
    //Setup uniform parameters
    glUseProgram(shader_program_id);                                                                           PRINT_OPENGL_ERROR();

    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_program_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();


    glBindTexture(GL_TEXTURE_2D,texture_default);  PRINT_OPENGL_ERROR();
    surface_opengl.draw();
}


scene::scene()
    :shader_program_id(0)
{}


GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}


void scene::load_common_data()
{
    texture_default=load_texture_file("data/white.jpg");
    shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag"); PRINT_OPENGL_ERROR();
}

