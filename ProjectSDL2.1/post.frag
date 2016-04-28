#version 430

in vec2 frag_uv;

out vec3 color;

uniform sampler2D texture;
uniform sampler2D texture2;
uniform float width;
uniform float height;

// Returns 0 if the value is below the threshold otherwise 1
float threshold(in float thr1, in float val)
{
	if(val < thr1){	return 0.0;}

	
	return val;
}

// Average pixel intensity from 3 color channels
float avgIntensity(in vec4 pix)
{
	return(pix.r + pix.g + pix.b) / 3.0;
}

// get a pixel from the texture with modified uv coordinates
vec4 getPixel(in vec2 uv, in float dx, in float dy)
{
	return texture2D(texture,uv + vec2(dx,dy));
}

// returns 0 if no edge and 1 if we found edge
float isEdge(in vec2 uv)
{
	float dxtex = 1.0 / width;
	float dytex = 1.0 / height; 
	float pix [9];
	int k = 0;
	float delta;

	//read neightboring pixel intensities
	for(int i =-1; i<2; i++)
	{
		for(int j = -1; j<2; j++)
		{
			
			pix[k] = avgIntensity(getPixel(uv,float(i)*dxtex,float(j)*dytex));
			k++;
		}
	}

	//average color differences around neighboring pixels
	delta = (abs(pix[1]-pix[7])+
			abs(pix[5]-pix[3])+
			abs(pix[0]-pix[8])+
			abs(pix[2]-pix[6]));

	return threshold(0.4,delta); // if the average color difference is too big we found an edge
}

void main()
{
	

	if(isEdge(frag_uv) > 0)
	{
		color = vec3(0,0,0);
	}
	else
	{
		color = vec3(texture2D(texture, frag_uv));
		//color = vec3(1,1,1);
	}
}