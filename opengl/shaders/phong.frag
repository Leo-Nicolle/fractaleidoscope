// "concon"
varying vec4 N ,L ,V,R;

void main()
{

	vec4 ambiant= gl_LightSource[0][0].ambient;
	vec4 diffus= gl_LightSource[0].diffuse * max(dot(N,L), 0.0);
	vec4 specular=  gl_LightSource[0].specular 
                * pow(max(dot(R,V),0.0),0.3*gl_FrontMaterial.shininess);
	gl_FragColor =  ambiant +diffus + specular;
}

