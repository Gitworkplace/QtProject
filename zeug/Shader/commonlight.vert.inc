#sgdefine COMMONLIGHT_VERT_INC //Define setzen um Mehrfache inkludierung auszuschliessen

#sginclude "://zeug/Shader/common.vert.inc"
#sginclude "://zeug/Shader/commonlightmatdefs.inc"
#sginclude "://zeug/Shader/commonlightmodels.inc"

vec3 eyePosition()
{
    return (modelViewMatrix * vertexPosition).xyz;
}

vec3 eyeNormalVec()
{
    return normalize(normalMatrix * vertexNormal);
}

vec3 eyeLightVec(vec3 lightViewPosition)
{
    return lightViewPosition - eyePosition().xyz;
}

vec3 eyeViewVec()
{
    return -normalize(eyePosition().xyz);
}

vec3 eyeReflectVec(vec3 lightViewDirection)
{
    return -reflect(lightViewDirection, eyeNormalVec());
}

vec3 phong(vec3 lightViewDirection, vec3 lightAmbient, vec3 lightDiffuse, vec3 lightSpecular, vec2 lightAttenuations)
{
    return phong(lightViewDirection, eyeViewVec(), eyeNormalVec(), lightAmbient, lightDiffuse, lightSpecular, lightAttenuations, vec3(1.0));
}
