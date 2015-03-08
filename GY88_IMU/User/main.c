/**
 *	Keil project example for MPU6050 6-axes
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_mpu6050.h"
#include "HMC5883l.h"
#include "imu.h"
#include <stdio.h>



void readSensors(TM_MPU6050_t *MPU6050_Data_ptr,Sensor_t *s);
void printSensors(Sensor_t *s);
void printHeading(Heading_t *h);

int main(void) {
	TM_MPU6050_t MPU6050_Data;
	Sensor_t s;
	Heading_t h;
	char str[120];
	//int16_t  MagneticHeading[3]={0};
	HMC5883L_Data_t MagneticHeading;
	/* Initialize system */
	SystemInit();

	/* Initialize delay */
	TM_DELAY_Init();
	
	/* Initialize USART, TX: PB6 */
	TM_USART_Init(USART1, TM_USART_PinsPack_2, 115200);
	
	/* Initialize MPU6050 sensor */
	if (TM_MPU6050_Init(&MPU6050_Data, TM_MPU6050_Device_0, TM_MPU6050_Accelerometer_8G, TM_MPU6050_Gyroscope_2000s) != TM_MPU6050_Result_Ok) {
		/* Display error to user */
		TM_USART_Puts(USART1, "MPU6050 Error\r\n");
		
		/* Infinite loop */
		while (1);
	}
	
	HMC5883L_Initialize();
	reset_gyro(&s,&h);
	while (1) {
		
		readSensors(&MPU6050_Data,&s);		
		accel_head(&s,&h);
		gyro_head(&s,&h);
		
		printSensors(&s);
		printHeading(&h);
		/* Little delay */
		Delayms(100);
	}
}



void readSensors(TM_MPU6050_t *MPU6050_Data_ptr, Sensor_t *s){ 
	HMC5883L_Data_t MagneticHeading;
	
	/* Read all data from sensor */
		TM_MPU6050_ReadAll(MPU6050_Data_ptr);
		HMC5883L_GetHeading(&MagneticHeading);
	//Sample sensor data as close as possible
	
	s->accel[sx]=(float)MPU6050_Data_ptr->Accelerometer_X;//4096.0f; //g
	s->accel[sy]=(float)MPU6050_Data_ptr->Accelerometer_Y;//4096.0f; //
	s->accel[sz]=(float)MPU6050_Data_ptr->Accelerometer_Z+737;//4096.0f+0.18f; //
	
	s->gyro[sx]=(float)MPU6050_Data_ptr->Gyroscope_X*0.061035156f; //degree per second
	s->gyro[sy]=(float)MPU6050_Data_ptr->Gyroscope_Y*0.061035156f; 
	s->gyro[sz]=(float)MPU6050_Data_ptr->Gyroscope_Z*0.061035156f;
	
	s->magnet[sx]=(float)MagneticHeading.X;
	s->magnet[sy]=(float)MagneticHeading.Y;
	s->magnet[sz]=(float)MagneticHeading.Z;
	
}


void printSensors(Sensor_t *s){
		char str[255];
	
			/* Format data */	
		sprintf(str, "Accelerometer\r\n- X:%5.1f\r\n- Y:%5.1f\r\n- Z:%5.1f\r\nGyroscope\r\n- X:%5.1f\r\n- Y:%5.1f\r\n- Z:%5.1f\r\nMagnetometer\r\n- X:%5.1f\r\n- Y:%5.1f\r\n- Z:%5.1f\r\n\r\n\r\n",
			s->accel[sx],
			s->accel[sy],
			s->accel[sz],
			s->gyro[sx],
			s->gyro[sy],
			s->gyro[sz],
			s->magnet[sx],
			s->magnet[sy],
			s->magnet[sz]
			
		);	
	
	 TM_USART_Puts(USART1,str);
}
void printHeading(Heading_t *h)
{
char str[255];
	
			/* Format data */	
		sprintf(str, "Accel Head\r\n- Pitch:%3.3f\r\n- Roll:%3.3f\r\nGyro Head\r\n- Pitch:%3.3f\r\n- Roll:%3.3f\r\n\r\n",
			h->accel[pitch],
			h->accel[roll],
			h->gyro[pitch],
			h->gyro[roll]
		);	
	
	 TM_USART_Puts(USART1,str);

}


