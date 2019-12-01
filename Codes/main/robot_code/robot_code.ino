#include<avr/io.h>
#include "PWM.h"
#include "MPU6050.h"
#include "PID.h"

#define F_CPU 16000000
#define I2C_CLOCK  100000L
#define MPU_ADDRESS 0x68 //Endereço do MPU6050

//Filter parameters
#define FILTER_WC 99999
#define FILTER_TS 0.01
double filter_a = MPU6050_GetFilterConstant(FILTER_WC, FILTER_TS);

//PID Controller parameters
PID_Settings PID_config;

int main()
{
    init(); // Inicializa o core do microcontrolador
    
    PID_config.KP = 60;
    PID_config.KI = 0;
    PID_config.KD = 0;
    PID_config.MaxOutput = 100;
    PID_config.MinOutput = -100;
    PID_config.MaxIntegral = 100;
    PID_config.MinIntegral = -100;
    PID_config.dt = 0.01;
    
    Serial.begin(9600);
    PWM_Init(); // Inicializa parametrizações do PWM
    MPU6050_Init(MPU_ADDRESS); // Inicializa parametrizações do MPU6050
    double offset = 0;
    for(int i = 0; i < 10 ; i++)
    {
      offset += MPU6050_GetAngle(MPU_ADDRESS, filter_a);
      _delay_ms(100);
    }
    offset /= 10;
    Serial.println(offset);
    while (1) 
    {
      double error = MPU6050_GetAngle(MPU_ADDRESS, filter_a);
      double output = PID_Calculate(&PID_config, offset, error);
      //Serial.print(error);
      //Serial.print(",");             
      //Serial.println(output);
      Motor_Control(output);
      _delay_ms(8);
      
    }
}
