uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec4 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColor;



void main(){

    vec4 spalte1=vec4(1, 0, 0, 0);
    vec4 spalte2=vec4(0, 1, 0, 0);
    vec4 spalte3=vec4(0, 0, 1, 0);
    vec4 spalte4=vec4(8, 4.5, -17, 1);
    mat4 newmodelViewMatrix = mat4(spalte1, spalte2, spalte3, spalte4);
    gl_Position = projectionMatrix * newmodelViewMatrix * vertexPosition;


}
