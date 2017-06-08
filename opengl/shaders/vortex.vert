// concon

uniform vec3 vort;


float rFunc(float z,float z0, float z1, float thetaMax)
{
	if (z<z0)
	{
		return 0.0;
	}
	else if (z>z1)
	{
		return thetaMax;
	}
	else
	{
		return thetaMax*(z- z0)/(z1-z0) ;
	}
}
float alphaFunc(vec4 pos, vec3 vortArgs)
{
		float r= rFunc(pos.z, vortArgs.x,vortArgs.y,vortArgs.z);
		return r * exp( - (pos.x*pos.x + pos.y*pos.y) );
}
vec4 twistFunc (vec4 pos, vec3 vortArgs)
{
		float alpha=alphaFunc(pos,vortArgs);
		mat4 mat = mat4(cos(alpha), -sin(alpha), 0 , 0,
								    sin(alpha),  cos(alpha), 0 , 0,
								     0    ,    0   , 1 , 0,
								     0    ,    0   , 0 , 1);
		//vec3 pos3 =vec3(pos.x,pos.y,pos.z);						 
		return mat * pos;
}


void main()
{	
			vec4 pos= gl_Vertex;
  	  gl_Position = gl_ModelViewProjectionMatrix * twistFunc(pos,vort);
}

