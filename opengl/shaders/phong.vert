// concon

varying vec3 N ,L ,V,R;

void main()
{	

		//on calcule tous les vecteurs: 
	//position dans le repere observateur: 
	 vec3 P = gl_Vertex * gl_ModelViewMatrix;
	//N=> la normale dans le repèreobservateur: 
		N= normalize( N* gl_NormalMatrix);
	//L => le vecteur de la lumière arrivant sur l'objet
	  L=  normalize(gl_Position*  vec3(gl_LightSource[0].position));
	//R => le vecteur reflection de lumière
		R=normalize(reflect( L ,N ));
	//V=> le vecteur objet-> observateur  	
		V= - vec3(gl_ModelViewMatrix * gl_Vertex);     

	
	gl_Position = ftransform();

	
}

