

#include <GL/glew.h>

#include "scene.hpp"

#include "../../lib/opengl/glutils.hpp"
#include "../../lib/perlin/perlin.hpp"
#include "../../lib/interface/camera_matrices.hpp"
#include "../interface/myWidgetGL.hpp"
#include "../../lib/mesh/mesh_io.hpp"

#include <cmath>
#include <string>
#include <sstream>


using namespace cpe;


void scene::load_scene()
{

    //*****************************************//
    // Preload default structure               //
    //*****************************************//
    texture_default = load_texture_file("data/white.jpg");
    shader_program_id = read_shader("shaders/shader_mesh.vert",
                                    "shaders/shader_mesh.frag");


    //*****************************************//
    // OBJ Mesh                                //
    //*****************************************//
    texture_dinosaur=load_texture_file("data/stegosaurus.jpg");
    mesh_dinosaur=load_mesh_file("data/stegosaurus.obj");
    mesh_dinosaur.transform_apply_auto_scale_and_center();
    mesh_dinosaur_opengl.fill_vbo(mesh_dinosaur);

    //*****************************************//
    // OFF Mesh                                //
    //*****************************************//
    mesh_camel=load_mesh_file("data/camel.off");
    mesh_camel.transform_apply_auto_scale_and_center();
    mesh_camel.transform_apply_scale(0.5f);
    mesh_camel.transform_apply_rotation({1.0f,0.0f,0.0f},-M_PI/2.0f);
    mesh_camel.transform_apply_rotation({0.0f,1.0f,0.0f}, 5*M_PI/6.0f);
    mesh_camel.transform_apply_translation({-0.55f,-0.0f,0.1f});
    mesh_camel.fill_color_xyz();
    mesh_camel_opengl.fill_vbo(mesh_camel);


    //*****************************************//
    // Generate user defined mesh              //
    //*****************************************//

    mesh_ground.add_vertex( {-1.0f,-0.25f,-1.0f} );
    mesh_ground.add_vertex( {-1.0f,-0.25f, 1.0f} );
    mesh_ground.add_vertex( { 1.0f,-0.25f, 1.0f} );
    mesh_ground.add_vertex( { 1.0f,-0.25f,-1.0f} );
    //note: we can use mesh.add_vertex({x,y,z})
    //          or mesh.add_vertex(vec3(x,y,z));

    mesh_ground.add_triangle_index({0,2,1});
    mesh_ground.add_triangle_index({0,3,2});

    mesh_ground.fill_empty_field_by_default();
    mesh_ground.fill_color( {0.8,0.9,0.8} );

    mesh_ground_opengl.fill_vbo(mesh_ground);

    // int Nu = 5;
    // int Nv = 5;
    // for (int kv=0; kv<Nv; kv++ ){
    //     for (int ku=0; ku<Nu; ku++ ){
    //       mesh_surface.add_vertex( {ku,kv,0.0f} );  
    //       mesh_surface.add_texture_coord( {ku,kv} );
    //       mesh_surface.add_normal( {0.0f,0.0f,1.0f} );
    //     }
    // }

    // for (int k=0; k<Nv*Nu; k++ ){
    //     if (((k+1)%(Nv)!=0) && ((k<Nv*(Nu-1)))){
    //         mesh_surface.add_triangle_index({k,k+1,k+Nv+1});
    //         mesh_surface.add_triangle_index({k,k+Nv,k+Nv+1});
    //     }
    // }

    // mesh_surface.fill_empty_field_by_default();
    // mesh_surface.fill_color( {1.0,0.0,0.0} );

    // mesh_surface_opengl.fill_vbo(mesh_surface);
    
}

void scene::tour(int N,int r, float h){
    float angle = 0;
    if (N%2!=0) {
        return;
    }
    else{
        float angle = 0.0;
        float x_cercle = 0.0;
        float y_cercle = 0.0;
        for(int i = 0; i < N ; i++)
        {
            angle = (i*360/(N/2)) * M_PI / 180;
            x_cercle = 0 + r * cos(angle);
            y_cercle = 0 + r * sin(angle);
            mesh_tour.add_vertex( {x_cercle,y_cercle,0} );
            mesh_tour.add_vertex( {x_cercle,y_cercle,h} );
        }

        for (int i=0;i<N;i=i+2){
            if (i==N-2){
                mesh_tour.add_triangle_index({i,i+1,0});
                mesh_tour.add_triangle_index({i+1,0,1});
            }
            else {
                mesh_tour.add_triangle_index({i,i+1,i+2});
                mesh_tour.add_triangle_index({i+1,i+2,i+3});
            }
        }
        //texture_gris = load_texture_file("data/gris.jpg");
        //texture_gris = load_texture_file("data/gris.jpg");

        mesh_tour.fill_empty_field_by_default();
        mesh_tour.fill_color( {1.0,0.0,0.8} );

        mesh_tour_opengl.fill_vbo(mesh_tour);

    }
}

void scene::surface_plane(int xmin,int xmax,int ymin,int ymax,int Nu,int Nv){
    float pas_x = static_cast<float>(xmax-xmin)/Nu;// diviser par nu-1 pour arriver à 1
    float pas_y = static_cast<float>(ymax-ymin)/Nv;

    auto z = perlin();
    float kz = 0.0;
    for (float kv=ymin; kv<Nv*pas_y; kv=kv+pas_y ){
        for (float ku=xmin; ku<Nu*pas_x; ku=ku+pas_x ){
            if (kv>0.4 && kv<0.6 && ku>0.1 && ku<0.9){
                kz = 0.2;
                mesh_surface.add_vertex( {ku,kv,kz} );
                mesh_surface.add_texture_coord({(kv-ymin)/(ymax-ymin),(ku-xmin)/(xmax-xmin)}); // mettre les texture a la bonne coordonné (0,0) pour le coin a gauche de notre image
            }
            else{
                kz = z(vec2(ku,kv))/3;
                mesh_surface.add_vertex( {ku,kv,kz} );
                mesh_surface.add_texture_coord({(kv-ymin)/(ymax-ymin),(ku-xmin)/(xmax-xmin)}); // mettre les texture a la bonne coordonné (0,0) pour le coin a gauche de notre image
            }
            
            //mesh_surface.add_color( {ku,kv,0.8} );
        }
    }


    for (int k=0; k<Nv*Nu; k++ ){
        if (((k+1)%(Nv)!=0) && ((k<Nv*(Nu-1)))){
            mesh_surface.add_triangle_index({k,k+1,k+Nv+1});
            mesh_surface.add_triangle_index({k,k+Nv,k+Nv+1});
        }
    }
    texture_herbe = load_texture_file("data/herbe.jpg");
    //texture_gris = load_texture_file("data/gris.jpg");

    mesh_surface.fill_empty_field_by_default();
    //mesh_surface.fill_color( {1.0,0.0,0.8} );

    mesh_surface_opengl.fill_vbo(mesh_surface);
};


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


    //Draw the meshes
    glBindTexture(GL_TEXTURE_2D,texture_dinosaur); PRINT_OPENGL_ERROR();
    mesh_dinosaur_opengl.draw();

    

    glBindTexture(GL_TEXTURE_2D,texture_herbe); PRINT_OPENGL_ERROR();
    //glBindTexture(GL_TEXTURE_2D,texture_gris); PRINT_OPENGL_ERROR();
    surface_plane(0,1,0,1,17,17);
    mesh_surface_opengl.draw();

    tour(18,1,0.5);
    mesh_tour_opengl.draw();

    glBindTexture(GL_TEXTURE_2D,texture_default);  PRINT_OPENGL_ERROR();
    mesh_camel_opengl.draw();
    mesh_ground_opengl.draw();
    

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


