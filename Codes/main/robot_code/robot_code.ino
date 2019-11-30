#include<avr/io.h>
#include "PWM.h"
#include "MPU6050.h"

#define F_CPU 16000000
#define I2C_CLOCK  100000L
#define MPU_ADDRESS 0x68 //Endereço do MPU6050

//Filter parameters
#define FILTER_WC 5
#define FILTER_TS 0.01
double filter_a = MPU6050_GetFilterConstant(FILTER_WC, FILTER_TS);
double last_value = 0;

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

int main()
{
    init(); // Inicializa o core do microcontrolador
    PWM_Init(); // Inicializa parametrizações do PWM
    MPU6050_Init(MPU_ADDRESS); // Inicializa parametrizações do MPU6050
    while (1) 
    {
      //MPU6050_GetAngle(MPU_ADDRESS, &last_value, double a);
      PWM_Control(50, 1);
      _delay_ms(3000);
      PWM_Control(-50, 1);
      _delay_ms(3000);
      PWM_Control(25, 1);
      _delay_ms(3000);
      PWM_Control(-25, 1);
      _delay_ms(3000);
    }
}
