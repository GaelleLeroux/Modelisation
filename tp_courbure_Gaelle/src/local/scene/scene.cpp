

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
}

float max(float x,float y){
    if (x>y){
        return x;
    }
}

vec3 colormap(float x) {
    return vec3(1.0, std::min(std::max(x,0.f),1.f), std::min(std::max(1.f-x,0.f),1.f));
}


void scene::build_surface_cylindrique()
{
    int const Nu=200;
    int const Nv=200;
    surface.set_plane_xy_unit(Nu,Nv);

    float const u_min = 0.0f;
    float const u_max = 2.0f*M_PI;
    float const v_min = 0.0f;
    float const v_max = 2.0f;

    float min_c=1000;
    float max_c=0;

    float const r = 0.2f;

    std::vector<float> liste_lambda;
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
            vec2 lambda = build_courbure_cylindrique(u,v,r);

            float Ks = lambda.x()*lambda.y();
            float Hs = 0.5* (lambda.x()+lambda.y());
           
            liste_lambda[ku*Nv+kv] = Hs;
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
            vec3 couleur;
            if (min_c!=max_c){
                couleur = colormap((liste_lambda[ku*Nv+kv]-min_c)/(max_c-min_c));
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

