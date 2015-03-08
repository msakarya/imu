#include "imu.h"
#include "math.h"

//~~~~~~~~~~~~~~~~  accel heading calculation  ~~~~~~~~~~~~~~~~~~~~~
void accel_head(Sensor_t *s,Heading_t *h)
	{
	
	float payda=0.0; 
	float p=0.0;
		
	//  accel pitch
	payda=sqrt(pow(s->accel[sx],2)+pow(s->accel[sz],2)); 
    if(payda<little)	//Prevent zero division error
    	payda=little;
		
		p=(float)180*atan(s->accel[sy]/payda)/pi;			
		
		if ( ( s->accel[sy] > 0 ) & ( s->accel[sz] > 0 ) )
			h->accel[pitch]= p;
else
		if ( ( s->accel[sy] > 0 ) & ( s->accel[sz] < 0 ) )
			h->accel[pitch]= (float)180 - p;
else
		if ( ( s->accel[sy] < 0 ) & ( s->accel[sz] > 0 ) )
			h->accel[pitch]= p;
else
		if ( ( s->accel[sy] < 0 ) & ( s->accel[sz] < 0 ) )
			h->accel[pitch]= -(float)180-p ;

		//  accel Roll
	payda=sqrt(pow(s->accel[sy],2)+pow(s->accel[sz],2));
		
		p=180.0*atan(s->accel[sx]/payda)/pi;	
		
		if ( ( s->accel[sx] > 0 ) & ( s->accel[sz] > 0 ) )
			h->accel[roll]= p;
else
		if ( ( s->accel[sx] > 0 ) & ( s->accel[sz] < 0 ) )
			h->accel[roll]= (float)180 - p;
else
		if ( ( s->accel[sx] < 0 ) & ( s->accel[sz] > 0 ) )
			h->accel[roll]= p;
else
		if ( ( s->accel[sx] < 0 ) & ( s->accel[sz] < 0 ) )
			h->accel[roll]= -(float)180-p ;
				
	}

void reset_gyro(Sensor_t *s,Heading_t *h)
	{
	uint8_t i,j;
	for(i=0;i<3;i++)
		{
		s->gyro_ref[i]=0;//s->gyro[i];	
		for(j=0;j<4;j++)				
			s->gyro4[i][j]=0;//s->gyro[i];
		h->gyro[i]=0;//h->accel[i];
		}	
	}
	
//~~~~~~~~~~~~~~~~  gyro heading calculation  ~~~~~~~~~~~~~~~~~~~~~
void gyro_head(Sensor_t *s,Heading_t *h)
	{
	
		uint8_t i,j;
	float Kcf=0.3;//0.03;
	
	for(i=0;i<3;i++)
		{
			float gi;
		s->gyro4[i][3]=(s->gyro[i]-s->gyro_ref[i])/2;
		
		//average out the last four samples
		gi=(s->gyro4[i][3]+s->gyro4[i][2]*2+s->gyro4[i][1]*2+s->gyro4[i][0])/6;
		//10Hz
		h->gyro[i]=h->gyro[i]+gi*0.1f-(h->gyro[i]-h->accel[i])*Kcf;
		
		for(j=0;j<3;j++)
			s->gyro4[i][j]=s->gyro4[i][j+1];
		
		h->final[i]=h->gyro[i];			
		
		}
	
	}

	
