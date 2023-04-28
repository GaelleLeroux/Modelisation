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

    //mat4 M(-1,3,-3,1, 3,-6,3,0, -3,3,0,0, 1,0,0,0) ;
    mat4 m(-1,3,-3,1, 3,-6,0,4, -3,3,3,1, 1,0,0,0) ;
    mat4 M = m/6;

    mat1x4 U1T (u*u*u,u*u,u,1);

    mat4x1 V1 (v*v*v,v*v,v,1);

    // float S = P(0,0)*(1-u)*(1-v) +
    //           P(0,3)*(1-u)*   v  +
    //           P(3,0)*   u *(1-v) +
    //           P(3,3)*   u *   v  ; // cette ligne est a modifier

    float S = U1T*transposed(M)*P*M*V1;

    

    return S;
}

float spline_evaluator::diff_u(float const u,float const v) const
{
    //mat4 M(-1,3,-3,1, 3,-6,3,0, -3,3,0,0, 1,0,0,0) ;
    mat4 m(-1,3,-3,1, 3,-6,0,4, -3,3,3,1, 1,0,0,0) ;
    mat4 M = m/6;

    mat1x4 U1T (3*u*u,2*u,1,0);

    mat4x1 V1 (v*v*v,v*v,v,1);
    // Ici il faut coder dS/du(u,v) = fonction(u,v,P),
    //  avec P etant les coordonnees x (resp. y,z) du polygone de controle

    float dS = U1T*transposed(M)*P*M*V1;
    return dS;
}

float spline_evaluator::diff_v(float const u,float const v) const
{
    //mat4 M(-1,3,-3,1, 3,-6,3,0, -3,3,0,0, 1,0,0,0) ;
    mat4 m(-1,3,-3,1, 3,-6,0,4, -3,3,3,1, 1,0,0,0) ;
    mat4 M = m/6;

    mat1x4 U1T (u*u*u,u*u,u,1);

    mat4x1 V1 (3*v*v,2*v,1,0);
    // Ici il faut coder dS/du(u,v) = fonction(u,v,P),
    //  avec P etant les coordonnees x (resp. y,z) du polygone de controle

    float dS = U1T*transposed(M)*P*M*V1;
    return dS;
}


}
