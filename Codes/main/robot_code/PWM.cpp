#include "PWM.h"

void PWM_Control(double dutyCicle, int roda) {
  //direcao 0 = horario; direcao 1 = anti-horario
  //roda 0 = roda do OCR0; roda 1 = roda do OCR2
  int valor = dutyCicle * 2.5;
  if (roda == 0) {
    if (dutyCicle >= 0) {
       OCR0A = 0;
       OCR0B = valor;
    } else {
       OCR0A = -valor;
       OCR0B = 0;
    }
  } else {
    if (dutyCicle >= 0) {
       OCR2A = 0;
       OCR2B = valor;
    } else {
       OCR2A = -valor;
       OCR2B = 0;
    }
  }
}

void PWM_Init()
{
  DDRB |= 0b00001000; //Pino 11 como saída
  DDRD |= 0b01101000; //Pinos 3, 5 e 6 como saída
  TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS00);
  TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
  TCCR2B |= (1 << CS20);
  OCR0A = 0;
  OCR0B = 0;
  OCR2A = 0;
  OCR2B = 0;
}

void Motor_Control(double Speed)
{
  Speed /= 2;
  if(Speed > 50)
    Speed = 50;
  if(Speed < -50)
    Speed = -50;
   
  PWM_Control(Speed, 0);
  PWM_Control(Speed * 1.3, 1);
}
