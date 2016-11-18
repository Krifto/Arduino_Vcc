#include <Vcc.h>
#include <LowPower.h>

#define VCC_MIN 2.0*0.6 // Minimum expected Vcc level, in Volts. Example for 2xAA Alkaline.
#define VCC_MAX 2.0*1.5 // Maximum expected Vcc level, in Volts. Example for 2xAA Alkaline.
#define VCC_CORRECTION 1.0/1.0 // Measured Vcc by multimeter divided by reported Vcc

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

  delay(200); //delay to allow serial to fully print before sleep

  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
}
