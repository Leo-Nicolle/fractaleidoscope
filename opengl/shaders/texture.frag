// "concon"
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float interp;

vec4 mymix(vec4 col1, vec4 col2, float inter){
	
	float inv = 1.0 - inter;

	float r = col1.r * inter + col2.r * inv;
	float g = col1.g * inter + col2.g * inv;
	float b = col1.b * inter + col2.b * inv;
	float a = col1.a * inter + col2.a * inv;


	return vec4( r,g,b,a);
	//return vec4(0.0,0.0,0.0,0.0);
}



void main()
{
	 //gl_FragColor = texture2D(tex1,gl_TexCoord[0].st);
	 vec4 color = texture2D(tex1,gl_TexCoord[0].st);
	 vec4 color2 = texture2D(tex2,gl_TexCoord[0].st);
	 vec4 color3 = mymix(color, color2, interp);
	 gl_FragColor = color3; 
}

