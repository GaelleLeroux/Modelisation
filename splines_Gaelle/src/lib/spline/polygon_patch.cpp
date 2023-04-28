
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


#include "polygon_patch.hpp"
#include "../3d/mat4.hpp"

#include "../common/error_handling.hpp"

namespace cpe
{
polygon_patch::polygon_patch()
    :data()
{}

polygon_patch::polygon_patch(vec3 const& p00,vec3 const& p01,vec3 const& p02,vec3 const& p03,
                               vec3 const& p10,vec3 const& p11,vec3 const& p12,vec3 const& p13,
                               vec3 const& p20,vec3 const& p21,vec3 const& p22,vec3 const& p23,
                               vec3 const& p30,vec3 const& p31,vec3 const& p32,vec3 const& p33)
    :data({{ p00,p01,p02,p03,
             p10,p11,p12,p13,
             p20,p21,p22,p23,
             p30,p31,p32,p33  }})
{}

const vec3& polygon_patch::operator()(int const ku ,int const kv) const
{
    ASSERT_CPE(ku>=0 && ku<4,"ku ("+std::to_string(ku)+") should be in [0,3]");
    ASSERT_CPE(kv>=0 && kv<4,"kv ("+std::to_string(kv)+") should be in [0,3]");

    return data[ku+4*kv];
}
vec3& polygon_patch::operator()(int const ku ,int const kv)
{
    ASSERT_CPE(ku>=0 && ku<4,"ku ("+std::to_string(ku)+") should be in [0,3]");
    ASSERT_CPE(kv>=0 && kv<4,"kv ("+std::to_string(kv)+") should be in [0,3]");

    return data[ku+4*kv];
}

mat4 polygon_patch::get_x() const
{
    return mat4(data[0].x(),data[4].x(),data[8 ].x(),data[12].x(),
                data[1].x(),data[5].x(),data[9 ].x(),data[13].x(),
                data[2].x(),data[6].x(),data[10].x(),data[14].x(),
                data[3].x(),data[7].x(),data[11].x(),data[15].x());
}
mat4 polygon_patch::get_y() const
{
    return mat4(data[0].y(),data[4].y(),data[8 ].y(),data[12].y(),
                data[1].y(),data[5].y(),data[9 ].y(),data[13].y(),
                data[2].y(),data[6].y(),data[10].y(),data[14].y(),
                data[3].y(),data[7].y(),data[11].y(),data[15].y());
}
mat4 polygon_patch::get_z() const
{
    return mat4(data[0].z(),data[4].z(),data[8 ].z(),data[12].z(),
                data[1].z(),data[5].z(),data[9 ].z(),data[13].z(),
                data[2].z(),data[6].z(),data[10].z(),data[14].z(),
                data[3].z(),data[7].z(),data[11].z(),data[15].z());
}
}
