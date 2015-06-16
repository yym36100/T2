uniform float mycolor;
varying vec4 v_Colour;

void main(void)
{
    gl_FragColor = vec4 ( 0.0,mycolor, 0.0, 0.5 );
}
