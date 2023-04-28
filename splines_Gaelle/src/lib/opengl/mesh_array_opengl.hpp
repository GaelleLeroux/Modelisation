/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifndef MESH_ARRAY_OPENGL_HPP
#define MESH_ARRAY_OPENGL_HPP

#include "mesh_opengl.hpp"
#include <vector>

namespace cpe
{
class spline_mesh_surface;

class mesh_array_opengl
{
public:

    /** Send the mesh data to the VBO, setup all vbos*/
    void fill_vbo(spline_mesh_surface const& s);

    /** Ask the GPU to draw the data.
     *  fill_vbo must have been called previously */
    void draw() const;

    /** Update the vertices (must already exists) */
    void update_vbo_vertex(spline_mesh_surface const& m);
    /** Update the normals (must already exists) */
    void update_vbo_normal(spline_mesh_surface const& m);

private:
    /** Internal data as a vector of mesh_opengl */
    std::vector<mesh_opengl> data;
};

}

#endif
