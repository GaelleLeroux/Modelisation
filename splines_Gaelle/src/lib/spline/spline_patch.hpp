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

#include "../3d/mat4.hpp"

namespace cpe
{
class polygon_patch;

/** Object enabling to compute a Spline Surface on a Patch
    Compute the function in R3 : S(u,v)=(S_x(u,v),S_y(u,v),S_z(u,v))
*/
class spline_patch
{
public:

    /** Create a Spline patch given a 4x4 control polygon */
    spline_patch(polygon_patch const& polygon);

    /** Evaluate the Spline at parameter (u,v): S(u,v) */
    vec3 operator()(float u,float v) const;

    /** Evaluate the derivative of the Spline in u direction at parameter (u,v): dS/du(u,v) */
    vec3 diff_u(float u,float v) const;
    /** Evaluate the derivative of the Spline in v direction at parameter (u,v): dS/dv(u,v) */
    vec3 diff_v(float u,float v) const;
    /** Evaluate the derivative normal of the surface at parameter (u,v) */
    vec3 normal(float u,float v) const;

private:
    /** Internal storage of the x coordinates of the 4x4 control polygon patch */
    mat4 polygon_x;
    /** Internal storage of the y coordinates of the 4x4 control polygon patch */
    mat4 polygon_y;
    /** Internal storage of the z coordinates of the 4x4 control polygon patch */
    mat4 polygon_z;
};

}
