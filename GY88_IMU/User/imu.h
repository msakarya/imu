#include <stdint.h>

typedef struct 
{
	float X,Y,Z;
} XYZ_t;

typedef struct 
{
	XYZ_t accel,gyro,gyro4[4],gyro_ref,magnet,magnet_tc;
} Sensor_t;

typedef struct
{
	float Roll,Pitch,Yaw;
} Head_t;

typedef struct
{
	Head_t accel,gyro,magnet,final;
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


