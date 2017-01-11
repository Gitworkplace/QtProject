#sginclude "://shaders/commonlightmatdefs.inc"
#sginclude "://shaders/commonlightmodels.inc"

in vec3 viewPosition;
in vec3 viewNormal;
in vec2 texCoords;
uniform float hasTexture=0.0f;
uniform sampler2D textureMap;

out vec4 fragColor;

void main()
{
    if(hasTexture > 0.5)
    {
        vec4 textureFrag = texture(textureMap, texCoords);
        fragColor = vec4(phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), textureFrag.rgb), 1.0);


    }
    else{
        fragColor = vec4(phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), vec3(1.0, 1.0, 1.0)), 1.0);


    }
    //vec3 color
    //vec3 color = lambert(viewPosition, -normalize(viewPosition), viewNormal, vec3(0.5, 0.5, 0.5));
    //fragColor = vec4(color + material.emission.rgb, computeMaterialAlpha());

}
