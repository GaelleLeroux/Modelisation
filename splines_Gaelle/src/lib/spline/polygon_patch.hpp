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

#ifndef polygon_patch_HPP
#define polygon_patch_HPP

#include "../3d/vec3.hpp"
#include <array>

namespace cpe
{
class mat4;

class polygon_patch
{
    public:

        // ********************************************* //
        // ********************************************* //
        //  CONSTRUCTORS
        // ********************************************* //
        // ********************************************* //

        /** \brief Empty constructor */
        polygon_patch();
        /** \brief Direct constructor */
        polygon_patch(vec3 const& p00,vec3 const& p01,vec3 const& p02,vec3 const& p03,
               vec3 const& p10,vec3 const& p11,vec3 const& p12,vec3 const& p13,
               vec3 const& p20,vec3 const& p21,vec3 const& p22,vec3 const& p23,
               vec3 const& p30,vec3 const& p31,vec3 const& p32,vec3 const& p33);

        // ********************************************* //
        // ********************************************* //
        //  Data
        // ********************************************* //
        // ********************************************* //

        /** \brief Get value */
        vec3 const& operator()(int ku ,int kv) const;
        /** \brief Get value */
        vec3& operator()(int ku ,int kv);

        /** \brief Get x coordinate in matrix4 form */
        mat4 get_x() const;
        /** \brief Get y coordinate in matrix4 form */
        mat4 get_y() const;
        /** \brief Get z coordinate in matrix4 form */
        mat4 get_z() const;

    private:

        /** \brief internal data */
        std::array<vec3,4*4> data;
};
}

#endif
