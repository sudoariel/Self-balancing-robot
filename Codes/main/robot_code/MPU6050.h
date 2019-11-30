void MPU6050_Init(int address);
double MPU6050_GetFilterConstant(double wc, double ts);
double MPU6050_GetAngle(int address, double* last_output, double a);
