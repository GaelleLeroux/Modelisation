#include "../../lib/mesh/mesh_parametric.hpp"
#include "../../lib/3d/vec3.hpp"
#include "../../lib/3d/vec2.hpp"
#include "../../lib/3d/mat2.hpp"

#include <cmath>
#include "methode.hpp"


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


cpe::vec2 build_courbure_cylindrique_discrete(const float& u,const float&  v,const float&  r,const int& Nu, const int& Nv, cpe::mesh_parametric& surface)
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

cpe::vec3 colormap(float x) {
    return cpe::vec3(1.0, std::min(std::max(x,0.f),1.f), std::min(std::max(1.f-x,0.f),1.f));
}
