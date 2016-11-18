#include <Vcc.h>

#define VCC_MIN 0.0
#define VCC_MAX 5.0
#define VCC_CORRECTION 1.0/1.0

Vcc vcc;

void setup()
{
  Serial.begin(115200);
}

void loop()
{  
  float v = vcc.Read_Volts(VCC_CORRECTION);
  Serial.print("VCC = ");
  Serial.print(v);
  Serial.println(" Volts");

  float p = vcc.Compute_Perc(v, VCC_MIN, VCC_MAX);
  Serial.print("VCC = ");
  Serial.print(p);
  Serial.println(" %");

  delay(2000);
}
