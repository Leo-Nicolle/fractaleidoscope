// concon

uniform vec3 twist;


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
vec4 twistFunc (vec4 pos, vec3 twistArgs)
{
		float r= rFunc(pos.z, twistArgs.x,twistArgs.y,twistArgs.z);
		
		mat4 mat = mat4(cos(r), -sin(r), 0 , 0,
								    sin(r),  cos(r), 0 , 0,
								     0    ,    0   , 1 , 0,
								     0    ,    0   , 0 , 1);
		//vec3 pos3 =vec3(pos.x,pos.y,pos.z);						 
		return mat * pos;
}


void main()
{	
			vec4 pos= gl_Vertex;
  	  gl_Position = gl_ModelViewProjectionMatrix * twistFunc(pos, twist);
}

