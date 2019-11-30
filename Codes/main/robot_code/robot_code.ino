#define F_CPU 16000000
#include<Wire.h>
#include<avr/io.h>
#include"PWM.h"
#define I2C_CLOCK  100000L
#define MPU_ADDRESS 0x68 //Endereço do MPU6050

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

int main()
{
    init(); // Inicializa o core do microcontrolador
    PWM_Init();
    while (1) 
    {
      PWM_Control(50, 0, 1);
      _delay_ms(3000);
      PWM_Control(50, 1, 1);
      _delay_ms(3000);
      PWM_Control(25, 0, 1);
      _delay_ms(3000);
      PWM_Control(25, 1, 1);
      _delay_ms(3000);
    }
}
