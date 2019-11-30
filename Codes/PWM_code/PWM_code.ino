#include <avr/io.h>

void PWM(int dutyCicle, int direcao, int roda) {
  //direcao 0 = horario; direcao 1 = anti-horario
  //roda 0 = roda do OCR0; roda 1 = roda do OCR2
  int valor = dutyCicle * 2.5;
  if (roda == 0) {
    if (direcao == 0) {
       OCR0A = 0;
       OCR0B = valor;
    } else {
       OCR0A = valor;
       OCR0B = 0;
    }
  } else {
    if (direcao == 0) {
       OCR2A = 0;
       OCR2B = valor;
    } else {
       OCR2A = valor;
       OCR2B = 0;
    }
  }
}


int main() {

  /* =============== SETUP INICIAL ===============  */
  /*  Pinos 5 e 6: Timer 0, Motor 1
   *  Pinos 3 e 11: Timer 2, Motor 2
  */
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
  
  while (1) {
    PWM(50, 0, 1);
     _delay_ms(3000);
    PWM(50, 1, 1);
     _delay_ms(3000);
    PWM(25, 0, 1);
     _delay_ms(3000);
    PWM(25, 1, 1);
     _delay_ms(3000);
  }
}
