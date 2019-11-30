#define F_CPU 16000000
#include<Wire.h>
#include<avr/io.h>
#define I2C_CLOCK  100000L
#define MPU_ADDRESS 0x68 //Endereço do MPU6050

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

int main()
{
    init(); // Inicializa o core do microcontrolador
    Serial.begin(9600);
    Wire.begin(); // Inicia comunicação serial
    Wire.beginTransmission(MPU_ADDRESS); // Inicia transmissão de dados para o MPU6050
    Wire.write(0x6B); // Seleciona registrador PWR_MGMT_1 do MPU6050 
    Wire.write(0); // Escreve 0x00 no registrador PWR_MGMT_1   
    Wire.endTransmission(true); // Encerra a transmissão
    _delay_ms(50);

    Wire.beginTransmission(MPU_ADDRESS); // Inicia transmissão de dados para o MPU6050
    Wire.write(0x1C); // Seleciona registrador ACCEL_CONFIG do MPU6050
    Wire.write(0x00); // Escreve 0x00 - Range de aceleração +-2g 
    Wire.endTransmission(true); // Encerra a transmissão
    _delay_ms(50);
   
      
    while(1)
    {   
      Wire.beginTransmission(MPU_ADDRESS); // Inicia transmissão de dados para o MPU6050
      Wire.write(0x3B); // Seleciona o registrador que contém os valores do acelerômetro e giroscópio
      Wire.endTransmission(false); // Encerra a transmissão
      Wire.requestFrom(MPU_ADDRESS,6,true); // Solicita 6 bytes com somente os dados do acelerômetro
      AcX=Wire.read()<<8|Wire.read();    
      AcY=Wire.read()<<8|Wire.read();  
      AcZ=Wire.read()<<8|Wire.read();  
      Serial.print(AcX);  
      Serial.print("\t"); Serial.print(AcY);
      Serial.print("\t"); Serial.println(AcZ); 
     
      _delay_ms(10);  
    }
     
}

    
