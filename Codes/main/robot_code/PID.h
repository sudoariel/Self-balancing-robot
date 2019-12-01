#include <avr/io.h>

typedef struct 
{
  double KP;
  double KI;
  double KD;
  double MaxOutput;
  double MinOutput;
  double MaxIntegral = 100;
  double MinIntegral = -100;
  double dt;
} PID_Settings;

double PID_Calculate(PID_Settings* settings, double setpoint, double current_position);
