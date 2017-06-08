// concon



void main()
{	

	// 3 solutions pour la mÃªme chose
    //gl_Position = ftransform();
//	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	


	
}

