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

#include "mesh_array_opengl.hpp"

#include "../spline/spline_mesh_surface.hpp"
#include "../common/error_handling.hpp"

namespace cpe
{

void mesh_array_opengl::fill_vbo(spline_mesh_surface const& s)
{
    int const Nu = s.size_patch_u();
    int const Nv = s.size_patch_v();

    int const N = Nu*Nv;

    if(static_cast<int> (data.size()) !=N)
        data.resize(N);


    for(int kv=0 ; kv<Nv ; ++kv)
    {
        for(int ku=0 ; ku<Nu ; ++ku)
        {
            int const offset = ku+Nu*kv;
            ASSERT_CPE(offset>=0 && offset<static_cast<int>(data.size()),"Incorrect offset");

            mesh_parametric const& current_surface=s.surface(ku,kv);
            ASSERT_CPE(current_surface.valid_mesh(),"Invalid surface");
            data[offset].fill_vbo(current_surface);
        }
    }


}

void mesh_array_opengl::draw() const
{
    for(auto const& surf : data)
        surf.draw();
}

void mesh_array_opengl::update_vbo_vertex(spline_mesh_surface const& s)
{
    int const Nu = s.size_patch_u();
    int const Nv = s.size_patch_v();

    int const N = Nu*Nv;

    ASSERT_CPE(static_cast<int>(data.size())==N,"Incorrect size");


    for(int kv=0 ; kv<Nv ; ++kv)
    {
        for(int ku=0 ; ku<Nu ; ++ku)
        {
            int const offset = ku+Nu*kv;
            ASSERT_CPE(offset>=0 && offset<static_cast<int>(data.size()),"Incorrect offset");

            mesh_parametric const& current_surface=s.surface(ku,kv);
            ASSERT_CPE(current_surface.valid_mesh(),"Invalid surface");
            data[offset].update_vbo_vertex(current_surface);
        }
    }
}

void mesh_array_opengl::update_vbo_normal(spline_mesh_surface const& s)
{
    int const Nu = s.size_patch_u();
    int const Nv = s.size_patch_v();

    int const N = Nu*Nv;

    ASSERT_CPE(static_cast<int>(data.size())==N,"Incorrect size");

    for(int kv=0 ; kv<Nv ; ++kv)
    {
        for(int ku=0 ; ku<Nu ; ++ku)
        {
            int const offset = ku+Nu*kv;
            ASSERT_CPE(offset>=0 && offset<static_cast<int>(data.size()),"Incorrect offset");

            mesh_parametric const& current_surface=s.surface(ku,kv);
            ASSERT_CPE(current_surface.valid_mesh(),"Invalid surface");
            data[offset].update_vbo_normal(current_surface);
        }
    }
}

}
