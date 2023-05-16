

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

#include "catenoide.hpp"
#include "cylindrique.hpp"
#include "sphere.hpp"
#include "para_hyper.hpp"
#include "helicoide.hpp"
#include "pseudo_sphere.hpp"


using namespace cpe;

void scene::build_surface_cylindrique()
{
    // cylindrique forme;
    // catenoide forme;
    // sphere forme;
    // para_hyper forme;
    helicoide forme;
    // pseudo_sphere forme;
    surface = forme.create(surface);

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

