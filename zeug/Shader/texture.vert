//#sginclude "://Shader/commonlight.vert.inc"

/*in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
*/
//out vec2 texCoords;
uniform mat4 projectionMatrix;
//uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;



vec4 vPos()
{
    vec4 spalte1=vec4(1, 0, 0, 0);
    vec4 spalte2=vec4(0, 1, 0, 0);
    vec4 spalte3=vec4(0, 0, 1, 0);
    vec4 spalte4=vec4(9, 4.5, -17, 1);
    mat4 newmodelViewMatrix = mat4(spalte1, spalte2, spalte3, spalte4);
    return projectionMatrix * newmodelViewMatrix * vertexPosition;
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
