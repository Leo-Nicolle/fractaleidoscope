// "concon"
varying vec3 P, N ,L ,V,R;
uniform sampler2D texN;
uniform sampler2D texC;
void main()
{

		/*vec3 Q1 = dFdx(P);
		vec3 Q2 = dFdy(P);
		vec2 st1 = dFdx(gl_TexCoord[0].st);
		vec2 st2 = dFdy(gl_TexCoord[0].st);
 //T=> la tangente dans le repere observateur
	vec3 T = normalize(Q1*st2.t - Q2*st1.t);
	//B=> vecteur binormal dans le repere observateur
	vec3 B = normalize(-Q1*st2.s + Q2*st1.s);


	 	N = 2.0 * texture2D (texN, gl_TexCoord[0].st).rgb - 1.0;
	 	
	 	N = normalize (N);
	 	B= normalize(cross(T,N) );
	
		mat3  transform= mat3(T.x, T.y,T.z,
							  B.x,B.y,B.z,
							  N.x,N.y,N.z
							);
		
		L= transform* L;
		V= transform* V;
	*/
	//calcul de ND:
	// distance= length(gl_TexCoord[0].st);

	vec4 ambiant=  gl_LightSource[0][0].ambient;
	//vec4 diffuseMaterial = texture2D (texC, gl_TexCoord[0].st);
	vec4 diffus= diffuseMaterial *gl_LightSource[0].diffuse * max(dot(N,L), 0.0);

//	vec4 specular=  gl_LightSource[0].specular 
  //              * pow(max(dot(R,V),0.0),0.3*gl_FrontMaterial.shininess);
                               
	gl_FragColor =  ambiant +diffus + specular;
	
	
		gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}

