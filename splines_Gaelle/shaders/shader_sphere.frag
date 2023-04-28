#version 120

uniform vec3 color;

varying vec4 position_3d_original;
varying vec4 position_3d_modelview;
varying vec3 normal;


uniform sampler2D texture;

uniform vec3 light=vec3(0.5f,0.3f,5.0f);


void main (void)
{
    vec3 n=normalize(normal);

    vec3 p=position_3d_modelview.xyz;
    vec3 vertex_to_light=normalize(light-p);
    vec3 reflected_light=reflect(-vertex_to_light,n);
    vec3 user_to_vertex=normalize(-p);

    float diffuse_term=0.8f*clamp(abs(dot(n,vertex_to_light)),0.0f,1.0f);
    float specular_term=0.8f*pow(clamp(dot(reflected_light,user_to_vertex),0.0f,1.0f),16.0f);
    float ambiant_term=0.4f;

    vec4 white=vec4(1.0,1.0,1.0,0.0);
    vec4 color_final=vec4(color,0.0);

    gl_FragColor = (ambiant_term+diffuse_term)*color_final+specular_term*white;

}
