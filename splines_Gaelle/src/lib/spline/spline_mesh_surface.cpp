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

#include "spline_mesh_surface.hpp"

#include "polygon_patch.hpp"
#include "spline_patch.hpp"

#include "../common/error_handling.hpp"

#include <array>

namespace cpe
{

spline_mesh_surface::spline_mesh_surface()
    :spline_mesh_surface(1,1,10,10)
{

}

spline_mesh_surface::spline_mesh_surface(int size_patch_u,int size_patch_v,int const samples_u,int const samples_v)
    :size_patch_u_data(size_patch_u),size_patch_v_data(size_patch_v),mesh_data()
{
    int const N=size_patch_u_data*size_patch_v_data;
    mesh_data.resize(N);

    vec3 const color_table[] = { { 0.5f,0.8f,0.4f }, {0.7f,0.2f,0.1f} , {0.4f,0.9f,0.1f} , {0.2f,0.2f,0.8f},
                                 {0.5f,0.5f,0.0f} , {0.5f,0.0f,0.5f} , {0.0f,0.5f,0.5f} , {0.1f,0.4f,0.9f},
                                 {0.5f,0.5f,0.5f} };
    int const size_color_table=sizeof(color_table)/sizeof(vec3);


    for(int ku=0;ku<size_patch_u_data;++ku)
    {
        for(int kv=0;kv<size_patch_v_data;++kv)
        {
            int const offset = ku+size_patch_u_data*kv;
            mesh_data[offset].set_plane_xy_unit(samples_u,samples_v);
            mesh_data[offset].fill_color(color_table[offset%size_color_table]);
        }
    }
}


void spline_mesh_surface::update_surface(polygon_grid const& control_polygon)
{
    ASSERT_CPE(control_polygon.size_patch_u()==size_patch_u_data,"Incorrect size");
    ASSERT_CPE(control_polygon.size_patch_v()==size_patch_v_data,"Incorrect size");
    ASSERT_CPE(static_cast<int>(mesh_data.size())==size_patch_u_data*size_patch_v_data,"Incorrect size");

    int const N_patch_u = size_patch_u_data;
    int const N_patch_v = size_patch_v_data;

    ASSERT_CPE(mesh_data.size()>0,"No surface to update");
    int const N_samples_u = mesh_data[0].size_u();
    int const N_samples_v = mesh_data[0].size_v();

    //Navigate through all patches
    for(int k_patch_u=0 ; k_patch_u<N_patch_u ; ++k_patch_u)
    {
        for(int k_patch_v=0 ; k_patch_v<N_patch_v ; ++k_patch_v)
        {
            //the current polygon patch
            polygon_patch const current_control_polygon = control_polygon.patch(k_patch_u,k_patch_v);
            spline_patch const patch(current_control_polygon);

            //get the current mesh
            int const offset = k_patch_u+N_patch_u*k_patch_v;
            mesh_parametric& mesh = mesh_data[offset];

            //Go through all vertices of the mesh
            for(int k_samples_u=0 ; k_samples_u<N_samples_u ; ++k_samples_u)
            {
                float const u = static_cast<float>(k_samples_u)/(N_samples_u-1);
                for(int k_samples_v=0 ; k_samples_v<N_samples_v ; ++k_samples_v)
                {
                    float const v = static_cast<float>(k_samples_v)/(N_samples_v-1);

                    //evaluate the spline
                    vec3 const p = patch(u,v);
                    vec3 const n = patch.normal(u,v);

                    //store the position into the mesh
                    mesh.vertex(k_samples_u,k_samples_v) = p;
                    mesh.normal(k_samples_u,k_samples_v) = n;
                }
            }
        }
    }
}

int spline_mesh_surface::size_patch_u() const
{
    return size_patch_u_data;
}
int spline_mesh_surface::size_patch_v() const
{
    return size_patch_v_data;
}
mesh_parametric const& spline_mesh_surface::surface(int const k_patch_u,int const k_patch_v) const
{
    int const Nu = size_patch_u();
    int const Nv = size_patch_v();

    ASSERT_CPE(k_patch_u>=0 && k_patch_u<Nu , "Incorrect index value, k_patch_u ("+std::to_string(k_patch_u)+") should be in [0,"+std::to_string(Nu)+"]");
    ASSERT_CPE(k_patch_v>=0 && k_patch_v<Nv , "Incorrect index value, k_patch_v ("+std::to_string(k_patch_v)+") should be in [0,"+std::to_string(Nv)+"]");

    int const offset = k_patch_u+Nu*k_patch_v;

    ASSERT_CPE(offset>=0 && offset<static_cast<int>(mesh_data.size()) , "Incorrect offset");

    return mesh_data[offset];
}


}
