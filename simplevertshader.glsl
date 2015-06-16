
uniform float mycolor;
attribute vec4 vertex;

void main(void)
{
	float s = sin(mycolor*6.28);
	float c = cos(mycolor*6.28);
        gl_Position = vec4(vertex.x*c - vertex.y*s, vertex.x*s + vertex.y*c,1.0,1.0);
}

