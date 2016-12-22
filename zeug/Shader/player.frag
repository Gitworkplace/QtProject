uniform bool  hasTexture=false;
//uniform sampler2D textureMap;

//in vec2 texCoords;
out vec4 fragColor;



void main()
{
    if(hasTexture)
    {
        //vec4 textureFrag = texture(textureMap, texCoords);
       // fragColor = vec4(textureFrag.rgb, textureFrag.a);
    }
   // fragColor = vec4(texCoords.x,texCoords.y,0.,1.);
    fragColor = vec4(.7f, 0.0f, .5f, 1.0f);
}
