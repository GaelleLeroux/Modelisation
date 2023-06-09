
/** TP 4ETI - CPE Lyon - 2013/2014 */

#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

//#include <GL/gl.h>
#include <GL/glew.h>

#include "../../lib/3d/mat3.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/mesh/mesh_parametric.hpp"
#include "../../lib/opengl/mesh_opengl.hpp"
#include "../../lib/interface/camera_matrices.hpp"

#include <vector>

#include "../../lib/3d/vec2.hpp"


class myWidgetGL;

class scene
{
public:

    scene();

    cpe::vec2 build_courbure_cylindrique(const float& u,const float&  v,const float&  r);
    cpe::vec2 build_courbure_chapeau(const float& u,const float&  v,const float&  r, const float& a, const float& b);

    cpe::vec2 build_courbure_cylindrique_discrete(const float& u,const float&  v,const float&  r,const int& Nu, const int& Nv);

    void build_surface_cylindrique();


    /** \brief Method called only once at the beginning (load off files ...) */
    void load_scene();

    /** \brief Method called at every frame */
    void draw_scene();

    /** Set the pointer to the parent Widget */
    void set_widget(myWidgetGL* widget_param);

    /** Load basic data for the scene */
    void load_common_data();


private:

    /** Load a texture from a given file and returns its id */
    GLuint load_texture_file(std::string const& filename);

    /** Access to the parent object */
    myWidgetGL* pwidget;

    /** Default id for the texture (white texture) */
    GLuint texture_default;

    /** The id of the shader do draw meshes */
    GLuint shader_program_id;


    cpe::mesh_parametric surface;
    cpe::mesh_opengl surface_opengl;


};

#endif
