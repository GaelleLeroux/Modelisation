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

#ifndef SPLINE_MESH_SURFACE_HPP
#define SPLINE_MESH_SURFACE_HPP

#include "polygon_grid.hpp"
#include "../mesh/mesh_parametric.hpp"

#include <vector>


namespace cpe
{
/** Store a full spline surface made of several patches */
class spline_mesh_surface
{
public:

    spline_mesh_surface();

    /** Init the surface with size_patch_u x size_patch_v patches, and each patch has samples_u x samples_v vertices */
    spline_mesh_surface(int size_patch_u,int size_patch_v,int samples_u,int samples_v);

    /** The number of patches in u direction */
    int size_patch_u() const;
    /** The number of patches in v direction */
    int size_patch_v() const;

    /** Get the spline surface for a given (ku,kv) patch */
    mesh_parametric const& surface(int k_patch_u,int k_patch_v) const;

    /** Update the mesh given the control polygon (vertices and normals) */
    void update_surface(polygon_grid const& control_polygon);

private:

    /** Internal number of patches in u direction */
    int size_patch_u_data;
    /** Internal number of patches in v direction */
    int size_patch_v_data;

    /** Internal storage for all the surfaces */
    std::vector<mesh_parametric> mesh_data;
};
}

#endif
