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

#ifndef SPLINE_EVALUATOR_HPP
#define SPLINE_EVALUATOR_HPP

namespace cpe
{
class mat4;

/** Helper class to evaluation a bicubic spline function */
class spline_evaluator
{
public:

    /** Init a spline evaluator given a 4x4 control polygon (a patch of control) */
    spline_evaluator(mat4 const& polygon_control);

    /** Evaluate the spline value at coordinate (u,v): S(u,v) */
    float operator()(float u,float v) const;
    /** Evaluate the differential in u coordinate at coordinate (u,v): dS(u,v)/du */
    float diff_u(float u,float v) const;
    /** Evaluate the differential in v coordinate at coordinate (u,v): dS(u,v)/dv */
    float diff_v(float u,float v) const;


private:

    /** The internal storage for the polygon data.
     * \note Only a reference is stored to the patch, no copy is made. The original data must live during the time of the evaluation. */
    mat4 const& P;
};

}

#endif
