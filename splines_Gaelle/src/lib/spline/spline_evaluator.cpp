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

#include "spline_evaluator.hpp"

#include "../3d/mat4.hpp"
#include "../3d/mat1x4.hpp"
#include "../3d/mat4x1.hpp"

namespace cpe
{

spline_evaluator::spline_evaluator(mat4 const& polygon_control)
    :P(polygon_control)
{}

float spline_evaluator::operator()(float const u,float const v) const
{
    // Ici il faut coder S(u,v) = fonction(u,v,P),
    //  avec P etant les coordonnees x (resp. y,z) du polygone de controle

    float S = P(0,0)*(1-u)*(1-v) +
              P(0,3)*(1-u)*   v  +
              P(3,0)*   u *(1-v) +
              P(3,3)*   u *   v  ; // cette ligne est a modifier

    return S;
}

float spline_evaluator::diff_u(float const u,float const v) const
{
    // Ici il faut coder dS/du(u,v) = fonction(u,v,P),
    //  avec P etant les coordonnees x (resp. y,z) du polygone de controle

    float dS = u+v; // cette ligne (code arbitrairement faux) est a modifier
    return dS;
}

float spline_evaluator::diff_v(float const u,float const v) const
{
    // Ici il faut coder dS/dv(u,v) = fonction(u,v,P),
    //  avec P etant les coordonnees x (resp. y,z) du polygone de controle

    float dS = u+v; // cette ligne (code arbitrairement faux) est a modifier
    return dS;
}


}
