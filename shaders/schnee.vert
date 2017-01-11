uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

uniform float Time;

void main(void)
{



    //vec3 sphereProj = vertexPosition;
    vec3 vertex;
    vec3 normal;
    //sphereProj = normalize(sphereProj);
    //normal = sphereProj;
    vec3 translate=vec3(10.0, -50.0, 0.0);
    vertex = mix(vertexPosition.xyz, vertexPosition.xyz+translate, Time);
    normal = mix(vertexNormal.xyz, normal, Time);
    normal = normalMatrix * normal;

    //gl_Position = projectionMatrix * vec4(vertex, 1.0);
    gl_Position=projectionMatrix*modelViewMatrix*vec4(vertex, 1.0);

}
