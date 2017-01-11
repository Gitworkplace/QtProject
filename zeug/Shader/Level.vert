#sginclude "://shaders/commonlight.vert.inc"
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;

out vec3 viewPosition;
out vec3 viewNormal;


void main()
{

    viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;


    gl_Position = vPos();//projectionMatrix * modelViewMatrix * vertexPosition;


}
