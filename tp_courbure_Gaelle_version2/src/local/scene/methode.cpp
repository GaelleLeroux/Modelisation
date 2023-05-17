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
float colormap_f1_supernova(float x) {
    return (0.3647 * x + 164.02) * x + 154.21;
}

float colormap_f2_supernova(float x) {
    return (126.68 * x + 114.35) * x + 0.1551;
}

float colormap_red_supernova(float x) {
    if (x < 0.0) {
        return 0.0;
    } else if (x < 0.136721748106749) {
        return colormap_f2_supernova(x) / 255.0;
    } else if (x < 0.23422409711017) {
        return (1789.6 * x - 226.52) / 255.0;
    } else if (x < 0.498842730309711) {
        return colormap_f1_supernova(x) / 255.0;
    } else if (x < 0.549121259378134) {
        return (-654.951781800243 * x + 562.838873112072) / 255.0;
    } else if (x < 1.0) {
        return ((3.6897 * x + 11.125) * x + 223.15) / 255.0;
    } else {
        return 237.0 / 255.0;
    }
}

float colormap_green_supernova(float x) {
    if (x < 0.0) {
        return 154.0 / 255.0;
    } else if (x < 3.888853260731947e-2) {
        return colormap_f1_supernova(x) / 255.0;
    } else if (x < 0.136721748106749e0) {
        return (-1455.86353067466 * x + 217.205447330541) / 255.0;
    } else if (x < 0.330799131955394) {
        return colormap_f2_supernova(x) / 255.0;
    } else if (x < 0.498842730309711) {
        return (1096.6 * x - 310.91) / 255.0;
    } else if (x < 0.549121259378134) {
        return colormap_f1_supernova(x) / 255.0;
    } else {
        return 244.0 / 255.0;
    }
}

float colormap_blue_supernova(float x) {
    if (x < 0.0) {
        return 93.0 / 255.0;
    } else if (x < 3.888853260731947e-2) {
        return (1734.6 * x + 93.133) / 255.0;
    } else if (x < 0.234224097110170) {
        return colormap_f1_supernova(x) / 255.0;
    } else if (x < 0.330799131955394) {
        return (-1457.96598791534 * x + 534.138211325166) / 255.0;
    } else if (x < 0.549121259378134) {
        return colormap_f2_supernova(x) / 255.0;
    } else if (x < 1.0) {
        return ((3.8931 * x + 176.32) * x + 3.1505) / 255.0;
    } else {
        return 183.0 / 255.0;
    }
}

vec3 colormap_supernova(float x) {
    return vec3(colormap_red_supernova(x), colormap_green_supernova(x), colormap_blue_supernova(x));
}

///////////////////////////////////////////////////////

vec3 colormap_idl16(float x) {
    if (x < 0.0) {
        return vec3(0.0, 0.0, 0.0);
    } else if (1.0 < x) {
        return vec3(1.0, 1.0, 1.0);
    } else if (x < 1.0 / 16.0) {
        return vec3(0.0, 84.0 / 255.0, 0.0);
    } else if (x < 2.0 / 16.0) {
        return vec3(0.0, 168.0 / 255.0, 0.0);
    } else if (x < 3.0 / 16.0) {
        return vec3(0.0, 1.0, 0.0);
    } else if (x < 4.0 / 16.0) {
        return vec3(0.0, 1.0, 84.0 / 255.0);
    } else if (x < 5.0 / 16.0) {
        return vec3(0.0, 1.0, 168.0 / 255.0);
    } else if (x < 6.0 / 16.0) {
        return vec3(0.0, 1.0, 1.0);
    } else if (x < 7.0 / 16.0) {
        return vec3(0.0, 0.0, 1.0);
    } else if (x < 8.0 / 16.0) {
        return vec3(128.0 / 255.0, 0.0, 1.0);
    } else if (x < 9.0 / 16.0) {
        return vec3(1.0, 0.0, 220.0 / 255.0);
    } else if (x < 10.0 / 16.0) {
        return vec3(1.0, 0.0, 180.0 / 255.0);
    } else if (x < 11.0 / 16.0) {
        return vec3(1.0, 0.0, 128.0 / 255.0);
    } else if (x < 12.0 / 16.0) {
        return vec3(1.0, 0.0, 64.0 / 255.0);
    } else if (x < 13.0 / 16.0) {
        return vec3(1.0, 0.0, 0.0);
    } else if (x < 14.0 / 16.0) {
        return vec3(220.0 / 255.0, 190.0 / 255.0, 190.0 / 255.0);
    } else if (x < 15.0 / 16.0) {
        return vec3(220.0 / 255.0, 220.0 / 255.0, 220.0 / 255.0);
    } else {
        return vec3(1.0, 1.0, 1.0);
    }
}