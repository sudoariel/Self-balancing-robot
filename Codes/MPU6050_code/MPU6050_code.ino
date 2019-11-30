#define F_CPU 16000000
#include<Wire.h>
#include<avr/io.h>
#include<math.h>
#define I2C_CLOCK  100000L
#define MPU_ADDRESS 0x68 //Endereço do MPU6050

//Filter parameters
#define FILTER_WC 5
#define FILTER_TS 0.01

double filter_a = (FILTER_WC * FILTER_TS) / (1 + ((FILTER_WC * FILTER_TS)));
double last_value = 0;

double GetAngle(double* last_output, double a)
{
  //Get raw data from MPU6050
  Wire.beginTransmission(MPU_ADDRESS); // Inicia transmissão de dados para o MPU6050
  Wire.write(0x3B); // Seleciona o registrador que contém os valores do acelerômetro e giroscópio
  Wire.endTransmission(false); // Encerra a transmissão
  Wire.requestFrom(MPU_ADDRESS,6,true); // Solicita 6 bytes com somente os dados do acelerômetro
  int16_t AcX=Wire.read()<<8|Wire.read();    
  int16_t AcY=Wire.read()<<8|Wire.read();  
  int16_t AcZ=Wire.read()<<8|Wire.read();

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
    Serial.println(GetAngle(&last_value, filter_a));
    _delay_ms(10);  
  }   
}

    
