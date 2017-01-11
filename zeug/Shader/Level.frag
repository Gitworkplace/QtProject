#sginclude "://shaders/commonlightmatdefs.inc"
#sginclude "://shaders/commonlightmodels.inc"

in vec4 color;
in vec3 viewPosition;
in vec3 viewNormal;


out vec4 fragColor;

void main()
{
    fragColor = vec4(phong(viewPosition, -normalize(viewPosition), normalize(viewNormal), vec3(1.0)), 1.0);
}
