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

#ifndef POLYGON_GRID_HPP
#define POLYGON_GRID_HPP

#include "../3d/vec3.hpp"
#include <vector>

namespace cpe
{

class polygon_patch;

/** Container of a control polygon
  * It is stored as a 2D grid of vertices.
  */
class polygon_grid
{
public:
    polygon_grid();

    /** Number of vertices in the u direction */
    int size_u() const;
    /** Number of vertices in the v direction */
    int size_v() const;

    /** Number of 4x4 patch in the u direction */
    int size_patch_u() const;
    /** Number of 4x4 patch in the v direction */
    int size_patch_v() const;

    /** Access to the vertex P(ku,kv) */
    vec3 const& operator()(int ku,int kv) const;
    /** Access to the vertex P(ku,kv) */
    vec3& operator()(int ku,int kv);

    /** Get the 4x4 patch given by its index (ku,kv) */
    polygon_patch patch(int k_patch_u,int k_patch_v) const;

    /** Add a new line of vertices (u direction) in the back of the grid */
    void add_back_u();
    /** Add a new line of vertices (u direction) in the front of the grid */
    void add_front_u();

    /** Add a new column of vertices (v direction) in the back of the grid */
    void add_back_v();
    /** Add a new column of vertices (v direction) in the front of the grid */
    void add_front_v();

    /** Delete a line of vertices (u direction) from the back of the grid (if possible) */
    void delete_back_u();
    /** Delete a line of vertices (u direction) from the front of the grid (if possible) */
    void delete_front_u();

    /** Delete a column of vertices (v direction) from the back of the grid (if possible) */
    void delete_back_v();
    /** Delete a column of vertices (v direction) from the front of the grid (if possible) */
    void delete_front_v();

    /** Duplicate all vertices on the border of the grid */
    void duplicate_boundary();


    /** Initialise the control polygon to be a (x,y) plane with z=0 */
    void set_planar_grid(int size_u_param,int size_v_param);
    
    void set_cylindrique_grid(int size_u_param,int size_v_param);

    void set_sphere_grid(int size_u_param,int size_v_param);

    /** Load the control polygon from a given file */
    void load_file(std::string const& filename);
    /** Save the control polygon in a given file */
    void save_file(std::string const& filename) const;

private:

    /** Resize the control polygon to a new size
      * Previously stored values are copied.
      *  Given P0 (previous control polygon) and P (new control polygon), we set
      *   P(ku+offset_u_dest,kv+offset_v_dest) = P0(ku+offset_u_ori,kv+offset_v_ori)
      */
    void resize(int size_u_param,int size_v_param,int offset_u_dest=0,int offset_v_dest=0,int offset_u_ori=0,int offset_v_ori=0);

    /** Internal storage of the number of vertices in u direction */
    int size_u_data;
    /** Internal storage of the number of vertices in v direction */
    int size_v_data;
    /** Internal storage of vertices */
    std::vector<vec3> vertex_data;

};


}

#endif
