#include "MPU6050.h"
#include<avr/io.h>
#include<math.h>
#include <util/delay.h>
#include<Wire.h>

void MPU6050_Init(int address)
{
  Wire.begin(); // Inicia comunicação serial
  Wire.beginTransmission(address); // Inicia transmissão de dados para o MPU6050
  Wire.write(0x6B); // Seleciona registrador PWR_MGMT_1 do MPU6050 
  Wire.write(0); // Escreve 0x00 no registrador PWR_MGMT_1   
  Wire.endTransmission(true); // Encerra a transmissão
  _delay_ms(50);
  
  Wire.beginTransmission(address); // Inicia transmissão de dados para o MPU6050
  Wire.write(0x1C); // Seleciona registrador ACCEL_CONFIG do MPU6050
  Wire.write(0x00); // Escreve 0x00 - Range de aceleração +-2g 
  Wire.endTransmission(true); // Encerra a transmissão
  _delay_ms(50);
}

double MPU6050_GetFilterConstant(double wc, double ts)
{
  return (wc * ts) / (1 + ((wc * ts)));
}

double MPU6050_GetAngle(int address, double* last_output, double a)
{
  //Get raw data from MPU6050
  Wire.beginTransmission(address); // Inicia transmissão de dados para o MPU6050
  Wire.write(0x3B); // Seleciona o registrador que contém os valores do acelerômetro e giroscópio
  Wire.endTransmission(false); // Encerra a transmissão
  Wire.requestFrom(address,6,true); // Solicita 6 bytes com somente os dados do acelerômetro
  int16_t AcX=Wire.read()<<8|Wire.read();    
  int16_t AcY=Wire.read()<<8|Wire.read();  
  int16_t AcZ=Wire.read()<<8|Wire.read();
  if(AcX == -1 && AcZ == -1)
    return 0;
    
  // Conversion to double
  double X = (double) AcX;
  double Z = (double) AcZ;
   
  // Calculate angle
  double angle = atan2(X,Z) * 90 / M_PI_2;
  
  // Filtering
  double output = a * angle + (1 - a) * *last_output;
   
  *last_output = output;     
  return output;  
}
