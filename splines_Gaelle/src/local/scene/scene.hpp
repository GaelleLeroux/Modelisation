

#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include "../../lib/spline/spline_mesh_surface.hpp"
#include "../../lib/opengl/mesh_array_opengl.hpp"
#include "../../lib/interface/selected_index.hpp"
#include "../../lib/opengl/line_opengl.hpp"

#include <vector>
#include <set>
#include <map>


class myWidgetGL;

class scene
{
public:

    /** Constructor */
    scene();



    /** \brief Method called only once at the beginning (load off files ...) */
    void load_scene();

    /** \brief Method called at every frame */
    void draw_scene();

    /** Set the pointer to the parent Widget */
    void set_widget(myWidgetGL* widget_param);

    /** Perform the picking of the vertices of the control polygon */
    void picking_polygon_grid(cpe::vec3 const& ray_center,cpe::vec3 const& ray_dir,bool addition_mode);

    /** Translates the picked vertices by the amount of translation */
    void translate_polygon_grid(cpe::vec3 const& translation);

    /** Add control polygon vertices */
    void add_u_back();
    /** Add control polygon vertices */
    void add_u_front();
    /** Add control polygon vertices */
    void add_v_back();
    /** Add control polygon vertices */
    void add_v_front();
    /** Delete control polygon vertices */
    void delete_u_back();
    /** Delete control polygon vertices */
    void delete_u_front();
    /** Delete control polygon vertices */
    void delete_v_back();
    /** Delete control polygon vertices */
    void delete_v_front();

    /** Recompute entirely the spline surface */
    void recompute_surface();
    /** Duplicated the boundary vertices of the control polygon */
    void duplicate_boundaries();
    /** Save the control polygon in a file */
    void save_control_polygon();
    /** Load the control polygon from a file */
    void load_control_polygon();

    /** Set the uniform_color variable */
    void set_uniform_color(bool uniform);
    /** Set the draw_spline variable */
    void set_draw_spline(bool draw);
    /** Set the draw_polygon_vertices variable */
    void set_draw_polygon_vertices(bool draw);
    /** Set the draw_polygon_line variable */
    void set_draw_polygon_line(bool draw);

private:

    /** Load a texture from a given file and returns its id */
    GLuint load_texture_file(std::string const& filename);

    /** Access to the parent object */
    myWidgetGL* pwidget;

    /** Default id for the texture (white texture) */
    GLuint texture_default;

    /** The id of the shader do draw the spline */
    GLuint shader_spline;
    /** The id of the shader do draw a sphere */
    GLuint shader_sphere;

    /** Load common datas such as shaders and textures */
    void load_common_data();

    /** If value up_to_date if false, recompute the spline surface and update the vertices and normals on the GPU */
    void update_spline_if_necessary();

    /** Load and setup the shader to draw the spline surface */
    void setup_shader_spline();
    /** Load and setup the shader to draw the vertices of the control polygon*/
    void setup_shader_sphere();
    /** Function drawing the control polygon (vertices and lines) */
    void draw_control_polygon();
    /** Load the current camera values on the given shader id */
    void send_camera_gpu(GLuint shader_id);

    /** Number of samples in u direction */
    int N_samples_u;
    /** Number of samples in v direction */
    int N_samples_v;


    /** The control polygon */
    cpe::polygon_grid control_polygon;
    /** The continuous spline data */
    cpe::spline_mesh_surface spline;
    /** The vbo storage to draw the spline */
    cpe::mesh_array_opengl spline_opengl;

    /** A helper class to draw a sphere */
    cpe::mesh_opengl sphere;
    /** The radius of the sphere of the vertices of the control polygon*/
    float const sphere_radius;

    /** The selected vertices of the polygon grid */
    cpe::selected_index selected_polygon_grid_index;

    /** Variable indicating if the spline surface need to be updated (after translating the vertices of the control polygon) */
    bool up_to_date;

    /** Indicates if the color of the spline is uniform or different for each patch */
    bool uniform_color;
    /** Indicates if the spline surface is drawn */
    bool draw_spline;
    /** Indicates if the vertices of the control polygon are drawn */
    bool draw_polygon_vertices;
    /** Indicates if the lines linking the vertices of the control polygon are drawn */
    bool draw_polygon_line;

    /** A helper class to draw lines */
    cpe::line_opengl line_drawer;


};

#endif
