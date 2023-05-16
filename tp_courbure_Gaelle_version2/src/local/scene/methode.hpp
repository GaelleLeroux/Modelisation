#include "../../lib/mesh/mesh_parametric.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"

#ifndef METHODE_HPP
#define METHODE_HPP

float min(float x,float y);

float max(float x,float y);


cpe::vec2 build_courbure_discrete(const float& u,const float&  v,const float&  r,const int& Nu, const int& Nv, cpe::mesh_parametric& surface);

cpe::vec2 build_courbure_analytique(const cpe::vec3& du,const cpe::vec3& dv,const cpe::vec3&  du2,const cpe::vec3&  dv2, const cpe::vec3&  dudv);

cpe::vec3 colormap(float x);

cpe::vec3 colormap_hsv_matlab(float x);

cpe::vec3 colormap_IDL_Haze(float x);

#endif