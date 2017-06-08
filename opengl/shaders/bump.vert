// concon

varying vec3  P,R, N ,L ,V,B,T;

void main()
{	

		//on calcule tous les vecteurs: 
	//position dans le repere observateur: 
	 P = gl_Vertex * gl_ModelViewMatrix;
	 //N=> la normale dans le repèreobservateur: 
		N= normalize( N* gl_NormalMatrix);
	
	
	
	//L => le vecteur de la lumière arrivant sur l'objet
	  L=  normalize(gl_Position*  vec3(gl_LightSource[0].position));
	
	//V=> le vecteur objet-> observateur  	
		V= - vec3(gl_ModelViewMatrix * gl_Vertex);     

	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position = ftransform();

	
}

