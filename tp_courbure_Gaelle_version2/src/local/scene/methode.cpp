#include "../../lib/mesh/mesh_parametric.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"

#include <cmath>
#include "methode.hpp"

using namespace cpe;

float min(float x,float y){
    if (x>y){
        return y;
    }
    else {
        return x;
    }
}

float max(float x,float y){
    if (x>y){
        return x;
    }
    else {
        return y;
    }
}


cpe::vec2 build_courbure_discrete(const float& u,const float&  v,const float&  r,const int& Nu, const int& Nv, cpe::mesh_parametric& surface)
{
    if (u!=0 and u!=Nu-1 and v!=0 and v!=Nv-1){
        cpe::mat2 Is(dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u+1,v)-surface.vertex(u-1,v))/2), 
                dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2), 
                dot((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2), 
                dot((surface.vertex(u,v+1)-surface.vertex(u,v-1))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2));

        cpe::vec3 n = normalized(cross((surface.vertex(u+1,v)-surface.vertex(u-1,v))/2,(surface.vertex(u,v+1)-surface.vertex(u,v-1))/2));

        cpe::mat2 IIs(dot((surface.vertex(u+1,v)-2*surface.vertex(u,v)+surface.vertex(u-1,v)),n), 
                dot((surface.vertex(u+1, v+1)-surface.vertex(u+1,v-1)-surface.vertex(u-1,v+1)+surface.vertex(u-1,v-1))/4,n), 
                dot((surface.vertex(u+1, v+1)-surface.vertex(u+1,v-1)-surface.vertex(u-1,v+1)+surface.vertex(u-1,v-1))/4,n), 
                dot((surface.vertex(u,v+1)-2*surface.vertex(u,v)+surface.vertex(u,v-1)),n));

        cpe::mat2 Ws = -IIs*inverse(Is);
        cpe::vec2 lambda = eigenvalue(Ws) ;
        // if (std::isnan(lambda.x()) || std::isnan(lambda.y())) {
        //     lambda.x() = 0;
        //     lambda.y() = 0;
        // }
        return lambda;
    }
    else {
        return cpe::vec2{0,0};
    };
}

cpe::vec2 build_courbure_analytique(const cpe::vec3& du,const cpe::vec3& dv,const cpe::vec3&  du2,const cpe::vec3&  dv2, const cpe::vec3&  dudv){
    mat2 Is(dot(du,du), 
            dot(du,dv), 
            dot(du,dv),
            dot(dv,dv));
            
    vec3 n = normalized(cross(du,dv))  ;

    mat2 IIs(dot(du2,n), 
            dot(dudv,n), 
            dot(dudv,n),
            dot(dv2,n));

    mat2 Ws = -IIs*inverse(Is);

    auto lambda = eigenvalue(Ws) ;

    return lambda;
}

cpe::vec3 colormap(float x) {
    return cpe::vec3(1.0, std::min(std::max(x,0.f),1.f), std::min(std::max(1.f-x,0.f),1.f));
}


float colormap_red_hsv_matlab(float x) {
    if (x < 0.5) {
        return -6.0 * x + 67.0 / 32.0;
    } else {
        return 6.0 * x - 79.0 / 16.0;
    }
}

float colormap_green_hsv_matlab(float x) {
    if (x < 0.4) {
        return 6.0 * x - 3.0 / 32.0;
    } else {
        return -6.0 * x + 79.0 / 16.0;
    }
}

float colormap_blue_hsv_matlab(float x) {
    if (x < 0.7) {
       return 6.0 * x - 67.0 / 32.0;
    } else {
       return -6.0 * x + 195.0 / 32.0;
    }
}


cpe::vec3 colormap_hsv_matlab(float x) {
    float r = min(max(colormap_red_hsv_matlab(x), 0.0), 1.0);
    float g = min(max(colormap_green_hsv_matlab(x), 0.0), 1.0);
    float b = min(max(colormap_blue_hsv_matlab(x), 0.0), 1.0);
    return vec3(r, g, b);
}
///////////////////////////////////
float colormap_red_IDL_Haze(float x) {
    if (x < 0.0) {
        return 167.0;
    } else if (x < (2.54491177159840E+02 + 2.49117061281287E+02) / (1.94999353031535E+00 + 1.94987400471999E+00)) {
        return -1.94987400471999E+00 * x + 2.54491177159840E+02;
    } else if (x <= 255.0) {
        return 1.94999353031535E+00 * x - 2.49117061281287E+02;
    } else {
        return 251.0;
    }
}

float colormap_green_IDL_Haze(float x) {
    if (x < 0.0) {
        return 112.0;
    } else if (x < (2.13852573128775E+02 + 1.42633630462899E+02) / (1.31530121382008E+00 + 1.39181683887691E+00)) {
        return -1.39181683887691E+00 * x + 2.13852573128775E+02;
    } else if (x <= 255.0) {
        return 1.31530121382008E+00 * x - 1.42633630462899E+02;
    } else {
        return 195.0;
    }
}

float colormap_blue_IDL_Haze(float x) {
    if (x < 0.0) {
        return 255.0;
    } else if (x <= 255.0) {
        return -9.84241021836929E-01 * x + 2.52502692064968E+02;
    } else {
        return 0.0;
    }
}

vec3 colormap_IDL_Haze(float x) {
    float t = x * 255.0;
    float r = colormap_red_IDL_Haze(t) / 255.0;
    float g = colormap_green_IDL_Haze(t) / 255.0;
    float b = colormap_blue_IDL_Haze(t) / 255.0;
    return vec3(r, g, b);
}

///////////////////////////////
