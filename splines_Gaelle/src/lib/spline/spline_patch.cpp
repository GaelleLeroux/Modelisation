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

#include "spline_patch.hpp"

#include "spline_evaluator.hpp"
#include "polygon_patch.hpp"
#include "../3d/vec3.hpp"

namespace cpe
{

spline_patch::spline_patch(polygon_patch const& polygon)
    :polygon_x(polygon.get_x()),polygon_y(polygon.get_y()),polygon_z(polygon.get_z())
{}

vec3 spline_patch::operator()(float const u,float const v) const
{
    spline_evaluator const Sx(polygon_x);
    spline_evaluator const Sy(polygon_y);
    spline_evaluator const Sz(polygon_z);

    return { Sx(u,v) , Sy(u,v) , Sz(u,v) };
}

vec3 spline_patch::diff_u(float const u,float const v) const
{
    spline_evaluator const Sx(polygon_x);
    spline_evaluator const Sy(polygon_y);
    spline_evaluator const Sz(polygon_z);

    return { Sx.diff_u(u,v) , Sy.diff_u(u,v) , Sz.diff_u(u,v) };
}

vec3 spline_patch::diff_v(float const u,float const v) const
{
    spline_evaluator const Sx(polygon_x);
    spline_evaluator const Sy(polygon_y);
    spline_evaluator const Sz(polygon_z);

    return { Sx.diff_v(u,v) , Sy.diff_v(u,v) , Sz.diff_v(u,v) };
}

vec3 spline_patch::normal(float const u,float const v) const
{

    //Ici il faut implementer le calcul de la normal
    // n = fonction(u,v)
    return vec3(0.0f,0.0*(u+v),1.0f); //cette ligne est fausse
}

}
