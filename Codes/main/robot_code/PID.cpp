#include "PID.h"

double PID_Calculate(PID_Settings* settings, double setpoint, double current_position)
{
  static double integral = 0;
  static double last_error = 0;
  double P = 0;
  double I = 0;
  double D = 0; 
  double error = current_position - setpoint;

  // Proporcional
  P = settings->KP * error;

  // Integral
  integral = integral + error * settings->dt;
  
  if(integral > settings->MaxIntegral)
    integral = settings->MaxIntegral;
  if(integral < settings->MinIntegral)
    integral = settings->MinIntegral;
  
  I = settings->KI * error;

  // Derivada
  D =  settings->KD * (error - last_error) / settings->dt;

  double output = P + I + D;
  if(output > settings->MaxOutput)
    output = settings->MaxOutput;
  if(output < settings->MinOutput)
      output = settings->MinOutput;
  
  return output;
}
