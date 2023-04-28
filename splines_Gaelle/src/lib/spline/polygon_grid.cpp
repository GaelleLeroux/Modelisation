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

#include "polygon_grid.hpp"

#include "polygon_patch.hpp"
#include "../common/error_handling.hpp"
#include "../common/math_base.hpp"

#include <fstream>

namespace cpe
{
polygon_grid::polygon_grid()
    :size_u_data(4),size_v_data(4),
      vertex_data({ {0.0f,0.0f,0.0f} , {0.0f,1.0f/3,0.0f} , {0.0f,2.0f/3,0.0f} , {0.0f,1.0f,0.0f} ,
                    {1.0f/3,0.0f,0.0f} , {1.0f/3,1.0f/3,0.0f} , {1.0f/3,2.0f/3,0.0f} , {1.0f/3,1.0f,0.0f} ,
                    {2.0f/3,0.0f,0.0f} , {2.0f/3,1.0f/3,0.0f} , {2.0f/3,2.0f/3,0.0f} , {2.0f/3,1.0f,0.0f} ,
                    {1.0f,0.0f,0.0f} , {1.0f,1.0f/3,0.0f} , {1.0f,2.0f/3,0.0f} , {1.0f,1.0f,0.0f} })
{}

int polygon_grid::size_u() const
{
    return size_u_data;
}
int polygon_grid::size_v() const
{
    return size_v_data;
}

int polygon_grid::size_patch_u() const
{
    return std::max(size_u_data-3,0);
}
int polygon_grid::size_patch_v() const
{
    return std::max(size_v_data-3,0);
}

vec3 const& polygon_grid::operator()(int const ku,int const kv) const
{
    ASSERT_CPE(ku>=0 && ku<size_u() , "Index ku ("+std::to_string(ku)+") should be between [0,"+std::to_string(size_u())+"]");
    ASSERT_CPE(kv>=0 && kv<size_v() , "Index kv ("+std::to_string(kv)+") should be between [0,"+std::to_string(size_v())+"]");

    int const offset = ku+size_u()*kv;

    ASSERT_CPE(offset>=0 && offset<static_cast<int>(vertex_data.size()),"Invalid offset size");

    return vertex_data[offset];

}
vec3& polygon_grid::operator()(int const ku,int const kv)
{
    ASSERT_CPE(ku>=0 && ku<size_u() , "Index ku ("+std::to_string(ku)+") should be between [0,"+std::to_string(size_u())+"]");
    ASSERT_CPE(kv>=0 && kv<size_v() , "Index kv ("+std::to_string(kv)+") should be between [0,"+std::to_string(size_v())+"]");

    int const offset = ku+size_u()*kv;

    ASSERT_CPE(offset>=0 && offset<static_cast<int>(vertex_data.size()),"Invalid offset size");

    return vertex_data[offset];
}

polygon_patch polygon_grid::patch(int const ku,int const kv) const
{
    ASSERT_CPE(ku>=0 && ku<size_patch_u() , "Index patch ku ("+std::to_string(ku)+") should be between [0,"+std::to_string(size_patch_u())+"]");
    ASSERT_CPE(kv>=0 && kv<size_patch_v() , "Index patch kv ("+std::to_string(kv)+") should be between [0,"+std::to_string(size_patch_v())+"]");

    auto const& S=*this;
    polygon_patch patch(S(ku+0,kv+0),S(ku+0,kv+1),S(ku+0,kv+2),S(ku+0,kv+3),
                        S(ku+1,kv+0),S(ku+1,kv+1),S(ku+1,kv+2),S(ku+1,kv+3),
                        S(ku+2,kv+0),S(ku+2,kv+1),S(ku+2,kv+2),S(ku+2,kv+3),
                        S(ku+3,kv+0),S(ku+3,kv+1),S(ku+3,kv+2),S(ku+3,kv+3));

    return patch;
}

void polygon_grid::add_back_u()
{
    int const Nu=size_u();
    resize(size_u()+1,size_v(),0,0);

    //add the last row
    for(int kv=0;kv<size_v();++kv)
    {
        vec3 const& p1 = (*this)(Nu-2,kv);
        vec3 const& p2 = (*this)(Nu-1,kv);

        vec3 const u = p2-p1;

        (*this)(Nu,kv) = p2+u;
    }
}

void polygon_grid::add_front_u()
{
    resize(size_u()+1,size_v(),1,0);

    //add the first row
    for(int kv=0;kv<size_v();++kv)
    {
        vec3 const& p1 = (*this)(2,kv);
        vec3 const& p2 = (*this)(1,kv);

        vec3 const u = p2-p1;

        (*this)(0,kv) = p2+u;
    }
}

void polygon_grid::add_back_v()
{
    int const Nv=size_v();
    resize(size_u(),size_v()+1,0,0);

    //add the last line
    for(int ku=0;ku<size_u();++ku)
    {
        vec3 const& p1 = (*this)(ku,Nv-2);
        vec3 const& p2 = (*this)(ku,Nv-1);

        vec3 const u = p2-p1;

        (*this)(ku,Nv) = p2+u;
    }
}

void polygon_grid::add_front_v()
{
    resize(size_u(),size_v()+1,0,1);

    //add the last line
    for(int ku=0;ku<size_u();++ku)
    {
        vec3 const& p1 = (*this)(ku,2);
        vec3 const& p2 = (*this)(ku,1);

        vec3 const u = p2-p1;

        (*this)(ku,0) = p2+u;
    }
}

void polygon_grid::delete_back_u()
{
    if(size_u()<=4) return ;
    resize(size_u()-1,size_v());
}

void polygon_grid::delete_front_u()
{
    if(size_u()<=4) return ;
    resize(size_u()-1,size_v(),0,0,1,0);
}

void polygon_grid::delete_back_v()
{
    if(size_v()<=4) return ;
    resize(size_u(),size_v()-1);
}

void polygon_grid::delete_front_v()
{
    if(size_v()<=4) return ;
    resize(size_u(),size_v()-1,0,0,0,1);
}

void polygon_grid::duplicate_boundary()
{
    resize(size_u()+2,size_v()+2,1,1);

    //fill the corners
    int const Nu=size_u();
    int const Nv=size_v();
    auto& S=*this;

    for(int ku=1 ; ku<Nu-1 ; ++ku)
    {
        S(ku,0)    = S(ku,1);
        S(ku,Nv-1) = S(ku,Nv-2);
    }
    for(int kv=1 ; kv<Nv-1 ; ++kv)
    {
        S(0,kv)    = S(1,kv);
        S(Nu-1,kv) = S(Nu-2,kv);
    }

    //4 corners
    S(0,0)       = S(1,1);
    S(Nu-1,0)    = S(Nu-2,0);
    S(0,Nv-1)    = S(0,Nv-2);
    S(Nu-1,Nv-1) = S(Nu-2,Nv-2);

}

void polygon_grid::resize(int const size_u_param,int const size_v_param ,
                          int const offset_u_dest,int const offset_v_dest,
                          int const offset_u_ori,int const offset_v_ori)
{

    ASSERT_CPE(size_u_param>3 && size_v_param>3,"Invalid size");

    polygon_grid const& S0=*this;

    //resize data storage
    polygon_grid S;
    S.vertex_data.resize(size_u_param*size_v_param);
    S.size_u_data=size_u_param;
    S.size_v_data=size_v_param;


    //copy the existing data
    int const Nu=std::min(size_u_param,size_u());
    int const Nv=std::min(size_v_param,size_v());
    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            int const u_dest = ku+offset_u_dest;
            int const v_dest = kv+offset_v_dest;
            int const u_ori = ku+offset_u_ori;
            int const v_ori = kv+offset_v_ori;

            ASSERT_CPE(u_dest>=0 && u_dest<S.size_u(),"Incorrect index");
            ASSERT_CPE(v_dest>=0 && v_dest<S.size_v(),"Incorrect index");
            ASSERT_CPE(u_ori>=0 && u_ori<S0.size_u(),"Incorrect index");
            ASSERT_CPE(v_ori>=0 && v_ori<S0.size_v(),"Incorrect index");

            S(u_dest,v_dest) = S0(u_ori,v_ori);
        }
    }


    *this=S;
}

void polygon_grid::save_file(std::string const& filename) const
{
    std::ofstream stream(filename.c_str());
    if(stream.good()!=true)
        throw exception_cpe("Cannot open file"+filename,EXCEPTION_PARAMETERS_CPE);

    auto const& G=*this;
    int const Nu = size_u();
    int const Nv = size_v();
    stream<<Nu<<" "<<Nv<<std::endl;
    for(int ku=0;ku<Nu;++ku)
    {
        for(int kv=0;kv<Nv;++kv)
        {
            vec3 const& p = G(ku,kv);
            stream<<p.x()<<" "<<p.y()<<" "<<p.z()<<std::endl;
        }
        stream<<std::endl;
    }
    stream.close();
}

void polygon_grid::load_file(std::string const& filename)
{
    std::ifstream stream(filename.c_str());
    if(stream.good()!=true)
        throw std::string("Cannot open file")+filename+" in "+__PRETTY_FUNCTION__;

    std::string buffer;

    int Nu = 0;
    int Nv = 0;
    stream>>Nu;
    stream>>Nv;

    if(Nu<3 || Nv<3 || Nu>5000 || Nv>5000)
        throw exception_cpe("Incorect size reading",EXCEPTION_PARAMETERS_CPE);

    polygon_grid G;
    G.resize(Nu,Nv);

    for(int ku=0 ; ku<Nu ; ++ku)
    {
        for(int kv=0 ; kv<Nv ; ++kv)
        {
            float x=0.0f;
            float y=0.0f;
            float z=0.0f;
            stream>>x;
            stream>>y;
            stream>>z;

            G(ku,kv)={x,y,z};
        }
    }

    stream.close();

    *this=G;
}

void polygon_grid::set_planar_grid(int const size_u_param,int const size_v_param)
{
    resize(size_u_param,size_v_param);

    auto& S=*this;
    for(int kv=0;kv<size_v_param;++kv)
    {
        float const v = static_cast<float>(kv)/(size_v_param-1);
        for(int ku=0;ku<size_u_param;++ku)
        {
            float const u = static_cast<float>(ku)/(size_u_param-1);

            S(ku,kv) = {u,v,0.0f};
        }
    }
}

void polygon_grid::set_cylindrique_grid(int const size_u_param,int const size_v_param)
{
    resize(size_u_param,size_v_param);

     auto& S=*this;
    for(int kv=0;kv<size_v_param;++kv)
    {
        float const v = static_cast<float>(kv)/(size_v_param-3);
        for(int ku=0;ku<size_u_param;++ku)
        {
            float const u = static_cast<float>(ku)/(size_u_param-3);

            S(ku,kv) = {cos(2*M_PI*u),sin(2*M_PI*v),0.0f};
        }
    }
}

void polygon_grid::set_sphere_grid(int const size_u_param,int const size_v_param)
{
    resize(size_u_param,size_v_param);

     auto& S=*this;
    for(int kv=0;kv<size_v_param;++kv)
    {
        float const v = static_cast<float>(kv)/(size_v_param-3);
        for(int ku=0;ku<size_u_param;++ku)
        {
            float const u = static_cast<float>(ku)/(size_u_param-3);

            S(ku,kv) = {cos(2*M_PI*u)*sin(M_PI*v),sin(2*M_PI*u)*sin(M_PI*v),cos(M_PI*v)};
        }
    }
}


}
