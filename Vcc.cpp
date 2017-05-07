/*
  Vcc - A supply voltage measuring library for Arduino

  Created by Ivo Pullens, Emmission, 2014
  
  Inspired by:
  http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Vcc.h"

#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define ADMUX_VCCWRT1V1 (_BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1))
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
#define ADMUX_VCCWRT1V1 (_BV(MUX5) | _BV(MUX0))
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define ADMUX_VCCWRT1V1 (_BV(MUX3) | _BV(MUX2))
#else
#define ADMUX_VCCWRT1V1 (_BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1))
#endif

float Vcc::readVolts(const float correction)
{
    // Read 1.1V reference against AVCC.
    // set the reference to VCC  and the measurement to the internal 1.1V reference.
    if (ADMUX != ADMUX_VCCWRT1V1) {
        ADMUX = ADMUX_VCCWRT1V1;

        // Bandgap reference start-up time: max 70us
        // Wait for Vref to settle.
        delayMicroseconds(350); 
    }
  
    // Start conversion and wait for it to finish.
    ADCSRA |= _BV(ADSC);
    while (bit_is_set(ADCSRA,ADSC)) {};
    // Result is now stored in ADC.
    // Calculate VCC (in V).
    float vcc = 1.1*1024.0f / ADC;
    
    // Apply compensation.
    vcc *= correction;
    return vcc;
}

float Vcc::Read_Volts(const float correction)
{
    return readVolts(correction);
}

float Vcc::readPerc(const float range_min, const float range_max, const boolean clip)
{
    return Vcc::computePerc(readVolts(),range_min, range_max, clip);
}

float Vcc::Read_Perc(const float range_min, const float range_max, const boolean clip){
        return readPerc(range_min, range_max, clip);
}

float Vcc::computePerc(const float volts_read, const float range_min, const float range_max, const boolean clip)
{
     // Read VCC and convert to percentage.
    float perc = 100.0f * (volts_read-range_min) / (range_max-range_min);
    // Clip to [0..100]% range, when requested.
    if (clip) {
        perc = constrain(perc, 0.0f, 100.0f);
    }
    return perc;
}
float Vcc::Compute_Perc(const float volts_read, const float range_min, const float range_max, const boolean clip)
{
        return computePerc(volts_read, range_min, range_max, clip);
}