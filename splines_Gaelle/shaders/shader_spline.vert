#version 120

uniform mat4 camera_projection;
uniform mat4 camera_modelview;
uniform mat4 normal_matrix;
uniform bool uniform_color;

varying vec4 position_3d_original;
varying vec4 position_3d_modelview;

varying vec3 normal;
varying vec4 color;


void main (void)
{
    gl_Position = camera_projection*camera_modelview*gl_Vertex;

    position_3d_original=gl_Vertex;
    position_3d_modelview=camera_modelview*gl_Vertex;

    if(uniform_color==false)
        color=gl_Color;
    else
        color=vec4(0.7,0.8,0.95,1.0);

    vec4 normal4d = normal_matrix*vec4(normalize(gl_Normal),0.0);
    normal = normal4d.xyz;

    gl_TexCoord[0]=gl_MultiTexCoord0;
}
