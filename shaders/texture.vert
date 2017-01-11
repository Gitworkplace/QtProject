#sginclude "://shaders/commonlight.vert.inc"


in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

out vec2 texCoords;
out vec3 viewPosition;
out vec3 viewNormal;

void main()
{
    viewPosition = eyePosition().xyz;
    viewNormal = eyeNormalVec().xyz;

    texCoords=textureCoords;
    gl_Position = vPos();
}
