

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"
#include "../../lib/interface/camera_matrices.hpp"
#include "../interface/myWidgetGL.hpp"
#include "../../lib/mesh/mesh_io.hpp"
#include "../../lib/intersection/intersection.hpp"

#include <cmath>
#include <string>
#include <sstream>


using namespace cpe;

void scene::load_scene()
{
    load_common_data();

    //number of samples for each patch of the spline surface


    //set up the control polygon
    control_polygon(1,1).z() = 0.7f; control_polygon(2,1).z() = 0.7f;
    control_polygon(1,2).z() = 0.7f; control_polygon(2,2).z() = 0.7f;

    //create the spline surface
    spline=spline_mesh_surface(control_polygon.size_patch_u(),
                               control_polygon.size_patch_v(),
                               N_samples_u,
                               N_samples_v);

    spline.update_surface(control_polygon);

    //send the spline surface on the GPU
    spline_opengl.fill_vbo(spline);
    up_to_date=true;

}

void scene::draw_scene()
{
    //update the vertices and the normal of the spline surface when needed
    update_spline_if_necessary();

    //load the shader and the uniform value for the spline surface
    setup_shader_spline();

    if(draw_spline)
        spline_opengl.draw(); //draw the spline surface on the screen

    //draw the control polygon
    draw_control_polygon();
}


scene::scene()
    :pwidget(nullptr),
      texture_default(0),
      shader_spline(0),
      shader_sphere(0),
      N_samples_u(25),
      N_samples_v(25),
      control_polygon(),
      spline(),
      spline_opengl(),
      sphere(),
      sphere_radius(0.02f),
      selected_polygon_grid_index(),
      up_to_date(true),
      uniform_color(true),
      draw_spline(true),
      draw_polygon_vertices(true),
      draw_polygon_line(true),
      line_drawer()
{}

void scene::load_common_data()
{
    texture_default=load_texture_file("data/white.jpg");

    //load some common shaders

    shader_spline = read_shader("shaders/shader_spline.vert",
                                    "shaders/shader_spline.frag");

    shader_sphere = read_shader("shaders/shader_sphere.vert",
                                        "shaders/shader_sphere.frag");

    //initialize the drawer of line
    line_drawer.init();

    //load a sphere
    mesh temp_sphere = load_mesh_file("data/sphere.obj");
    temp_sphere.transform_apply_auto_scale_and_center();
    temp_sphere.fill_color( {1.0f,0.0f,0.0f} );
    sphere.fill_vbo(temp_sphere);
}


void scene::update_spline_if_necessary()
{
    if(up_to_date==false)
    {
        spline.update_surface(control_polygon);
        spline_opengl.update_vbo_vertex(spline);
        spline_opengl.update_vbo_normal(spline);
        up_to_date=true;
    }

}

void scene::draw_control_polygon()
{
    //first draw the spheres
    if(draw_polygon_vertices)
    {
        int const Nu=control_polygon.size_u();
        int const Nv=control_polygon.size_v();

        setup_shader_sphere();
        for(int ku=0 ; ku<Nu ; ++ku)
        {
            for(int kv=0 ; kv<Nv ; ++kv)
            {
                auto const& p=control_polygon(ku,kv);
                glUniform3f(get_uni_loc(shader_sphere,"translation"),p.x(),p.y(),p.z());  PRINT_OPENGL_ERROR();
                if(selected_polygon_grid_index.exist(ku,kv))
                {glUniform3f(get_uni_loc(shader_sphere,"color"),1.0f,1.0f,0.0);           PRINT_OPENGL_ERROR();}
                else
                {glUniform3f(get_uni_loc(shader_sphere,"color"),1.0f,0.0f,0.0);           PRINT_OPENGL_ERROR();}
                sphere.draw();
            }
        }
    }

    //then draw the lines of the control polygon
    if(draw_polygon_line)
    {
        glUseProgram(line_drawer.shader_id());                                                                           PRINT_OPENGL_ERROR();

        camera_matrices const& cam=pwidget->camera();
        glUniformMatrix4fv(get_uni_loc(line_drawer.shader_id(),"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
        glUniformMatrix4fv(get_uni_loc(line_drawer.shader_id(),"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();

        int const Nu=control_polygon.size_u();
        int const Nv=control_polygon.size_v();
        for(int ku=0 ; ku<Nu-1 ; ++ku)
        {
            for(int kv=0 ; kv<Nv-1 ; ++kv)
            {
                auto const& p00 = control_polygon(ku,kv);
                auto const& p10 = control_polygon(ku+1,kv);
                auto const& p01 = control_polygon(ku,kv+1);
                auto const& p11 = control_polygon(ku+1,kv+1);

                line_drawer.draw(p00,p10); line_drawer.draw(p00,p01);
                line_drawer.draw(p01,p11); line_drawer.draw(p10,p11);
            }
        }
    }

}

GLuint scene::load_texture_file(std::string const& filename)
{
    return pwidget->load_texture_file(filename);
}

void scene::set_widget(myWidgetGL* widget_param)
{
    pwidget=widget_param;
}

void scene::translate_polygon_grid(cpe::vec3 const& translation)
{
    for(auto& p : selected_polygon_grid_index)
    {
        int const ku = p.first;
        int const kv = p.second;

        control_polygon(ku,kv) += translation;
        up_to_date=false;
    }
}

void scene::setup_shader_spline()
{
    //Setup uniform parameters
    glUseProgram(shader_spline);                                                                   PRINT_OPENGL_ERROR();
    send_camera_gpu(shader_spline);
    glUniform1i(get_uni_loc(shader_spline,"uniform_color"),uniform_color);                         PRINT_OPENGL_ERROR();
}

void scene::setup_shader_sphere()
{
    glUseProgram(shader_sphere);                                                               PRINT_OPENGL_ERROR();
    send_camera_gpu(shader_sphere);
    glUniform1f(get_uni_loc(shader_sphere,"scale"),sphere_radius);                             PRINT_OPENGL_ERROR();
}

void scene::send_camera_gpu(GLuint const shader_id)
{
    //Get cameras parameters (modelview,projection,normal).
    camera_matrices const& cam=pwidget->camera();

    //Set Uniform data to GPU
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_modelview"),1,false,cam.modelview.pointer());     PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"camera_projection"),1,false,cam.projection.pointer());   PRINT_OPENGL_ERROR();
    glUniformMatrix4fv(get_uni_loc(shader_id,"normal_matrix"),1,false,cam.normal.pointer());           PRINT_OPENGL_ERROR();

}

void scene::picking_polygon_grid(cpe::vec3 const& ray_center,
                                 cpe::vec3 const& ray_dir,
                                 bool const addition_mode)
{


    int const Nu=control_polygon.size_u();
    int const Nv=control_polygon.size_v();

    int ku_intersection = 0;
    int kv_intersection = 0;

    float intersection_parameter=0.0f;
    bool first_intersection=true;

    for(int ku=0;ku<Nu;++ku)
    {
        for(int kv=0;kv<Nv;++kv)
        {
            vec3 const& p=control_polygon(ku,kv);

            //compute intersection
            float intersection_0=0.0f;
            float intersection_1=0.0f;
            bool const is_intersection=cpe::intersection::sphere_ray(p,sphere_radius,ray_center,ray_dir,intersection_0,intersection_1);
            float const t=0.5f*(intersection_0+intersection_1);


            if(is_intersection)
            {
                //store the intersection and the indices if it is the first intersection
                // note an intersection is valid only if t>0 (intersection in front of the camera)
                if(t>=0 && (t<intersection_parameter || first_intersection) )
                {
                    ku_intersection=ku;
                    kv_intersection=kv;
                    intersection_parameter=t;
                    first_intersection=false;
                }
            }

        }
    }

    if(first_intersection==false)
    {
        if(addition_mode) // a left click on a vertex select it
            selected_polygon_grid_index.add(ku_intersection,kv_intersection);
        else // a right click on a vertex deselect it
            selected_polygon_grid_index.remove(ku_intersection,kv_intersection);
    }
    else if(addition_mode==false) // a right click on the empty space deselect all the vertices
        selected_polygon_grid_index.clear();

}

void scene::add_u_back()
{
    control_polygon.add_back_u();
    recompute_surface();
}
void scene::add_u_front()
{
    control_polygon.add_front_u();
    recompute_surface();
}
void scene::add_v_back()
{
    control_polygon.add_back_v();
    recompute_surface();
}
void scene::add_v_front()
{
    control_polygon.add_front_v();
    recompute_surface();
}

void scene::delete_u_back()
{
    control_polygon.delete_back_u();
    recompute_surface();
}
void scene::delete_u_front()
{
    control_polygon.delete_front_u();
    recompute_surface();
}
void scene::delete_v_back()
{
    control_polygon.delete_back_v();
    recompute_surface();
}
void scene::delete_v_front()
{
    control_polygon.delete_front_v();
    recompute_surface();
}

void scene::duplicate_boundaries()
{
    control_polygon.duplicate_boundary();
    recompute_surface();
}

void scene::recompute_surface()
{
    spline=spline_mesh_surface(control_polygon.size_patch_u(),control_polygon.size_patch_v(),N_samples_u,N_samples_v);
    spline.update_surface(control_polygon);
    spline_opengl.fill_vbo(spline);
}

void scene::save_control_polygon() {control_polygon.save_file("control_polygon.txt");}
void scene::load_control_polygon() {control_polygon.load_file("control_polygon.txt");recompute_surface();}

void scene::set_uniform_color(bool const uniform) {uniform_color=uniform;}
void scene::set_draw_spline(bool const draw) {draw_spline=draw;}

void scene::set_draw_polygon_vertices(bool const draw) {draw_polygon_vertices=draw;}
void scene::set_draw_polygon_line(bool const draw) {draw_polygon_line=draw;}


