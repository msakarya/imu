#include "imu.h"
#include "math.h"

//~~~~~~~~~~~~~~~~  accel heading calculation  ~~~~~~~~~~~~~~~~~~~~~
void accel_head(Sensor_t *s,Heading_t *h)
	{
	
	float payda=0.0; 
	float p=0.0;
		
	//  accel pitch
	payda=sqrt(pow(s->accel.X,2)+pow(s->accel.Z,2)+pow(s->accel.Y,2)); //
    if(payda<little)	//Prevent zero division error
    	payda=little;
		p=atan(s->accel.Y/payda);			
		
		if ( ( s->accel.Y > 0 ) & ( s->accel.Z > 0 ) )
			h->accel.Pitch= p;
else
		if ( ( s->accel.Y > 0 ) & ( s->accel.Z < 0 ) )
			h->accel.Pitch= pi_p5 - p;
else
		if ( ( s->accel.Y < 0 ) & ( s->accel.Z > 0 ) )
			h->accel.Pitch= p;
else
		if ( ( s->accel.Y < 0 ) & ( s->accel.Z < 0 ) )
			h->accel.Pitch= -pi_p5-p ;

		p=atan(s->accel.X/payda);	
		
		if ( ( s->accel.X > 0 ) & ( s->accel.Z > 0 ) )
			h->accel.Roll= p;
else
		if ( ( s->accel.X > 0 ) & ( s->accel.Z < 0 ) )
			h->accel.Roll= pi_p5 - p;
else
		if ( ( s->accel.X < 0 ) & ( s->accel.Z > 0 ) )
			h->accel.Roll= p;
else
		if ( ( s->accel.X < 0 ) & ( s->accel.Z < 0 ) )
			h->accel.Roll= -pi_p5-p ;
		
		
		/*
    //  accel roll
    payda=sqrt(pow(s->accel.Y,2)+pow(s->accel.Z,2));
    if(payda<little)	
    	payda=little;
    h->accel.Roll=atan(s->accel.X/payda); 
		
		*/
/*		
		//  accel yaw		
		payda=sqrt(pow(s->accel.Y,2)+pow(s->accel.X,2));
    if(payda<little)	
    	payda=little;
    h->accel.Yaw=pi-atan(s->accel.Z/payda);  
		*/		
		
		//  accel yaw		
		/*		
    
    payda=s->accel.Y;
    if((payda<little)&(payda>-little))	
    	{
    	if(payda>0)
    		payda=little;
    	else
    		payda=-little;
    	}
			
    if(s->accel.Y>0) 
			h->accel.Yaw=pi_p5+atan(s->accel.X/payda);      	         
    else    
    	h->accel.Yaw=pi_1p5-atan(-s->accel.X/payda);                
	*/
		
	}

