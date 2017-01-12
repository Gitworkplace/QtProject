//#sginclude "://Shader/commonlight.vert.inc"

/*in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform mat4 projectionMatrix;

uniform mat3 normalMatrix;
*/
//out vec2 texCoords;
uniform mat4 projectionMatrix;
//uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;



vec4 vPos()
{
    return projectionMatrix * modelViewMatrix * vertexPosition;
}

void main()
{
    //vec3 viewPosition = eyePosition().xyz;
    //vec3 viewDirection = -normalize(viewPosition);
    //vec3 vertexColor = phong(viewPosition, viewDirection, eyeNormalVec().xyz, vec3(1.0));
    //color = vec4(vertexColor, computeMaterialAlpha());

    gl_Position = vPos();


    //gl_Position = projectionMatrix * modelViewMatrix * vertexPosition;


            //ftransform();//

    //texCoords=textureCoords;
}
