// concon

uniform vec3 scale;

void main()
{	
	
			//vec3 scale= vec3(1,2,1);
			vec4 pos= gl_Vertex;
			pos.x= pos.x* scale.x;
			pos.y= pos.y* scale.y;
			pos.z= pos.z* scale.z;
	// 3 solutions pour la mÃªme chose

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * (pos) ;
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	  //gl_Position = ftransform();

	
}

