#include <stdint.h>

#define sx 0
#define sy 1
#define sz 2
#define pitch 0
#define roll 1
#define yaw 2

	typedef struct 
	{
		float X,Y,Z;
	} XYZ_t;
	
typedef struct 
{
	float accel[3],gyro[3],gyro4[3][4],gyro_ref[3],magnet[3],magnet_tc[3];
} Sensor_t;

typedef struct
{
	float Roll,Pitch,Yaw;
} Head_t;

typedef struct
{
	float accel[3],gyro[3],magnet[3],final[3];
} Heading_t;



void accel_head(Sensor_t *s,Heading_t *h);
void gyro_head(Sensor_t *s,Heading_t *h);
void compass_head(Sensor_t *s,Heading_t *h);
void reset_gyro(Sensor_t *s,Heading_t *h);

//~~~~~~~~~~~~  GLOBAL VARIABLES  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const float pi = 3.1415926535; 
static const float pi_p5 = 1.570796327; //pi* .5
static const float pi_1p5 = 4.71238898; //pi* 1.5
static const float little = 0.0000001; 


