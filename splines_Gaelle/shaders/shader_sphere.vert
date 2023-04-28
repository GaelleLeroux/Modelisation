#version 120

uniform vec3 translation;
uniform float scale;

uniform mat4 camera_projection;
uniform mat4 camera_modelview;
uniform mat4 normal_matrix;

varying vec4 position_3d_original;
varying vec4 position_3d_modelview;
varying vec3 normal;


void main (void)
{

    vec4 p = gl_Vertex;
    p.xyz *= scale;
    p.xyz += translation;
    gl_Position = camera_projection*camera_modelview*p;

    position_3d_original = p;
    position_3d_modelview = camera_modelview*p;

    vec4 normal4d = normal_matrix*vec4(normalize(gl_Normal),0.0);
    normal = normal4d.xyz;
}
