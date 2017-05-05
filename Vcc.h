/*
 VCC - A supply voltage measuring library for Arduino

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

#ifndef VCC_H
#define VCC_H

#include "Arduino.h"

class Vcc
{
  public:
    /**
     * Retrieve current VCC level.
     *
 	   * @param correction  Correction factor, when reported VCC is off from measured (externally) VCC
     *                    (due to variations in bandgap voltage of +/- 0.1V)
     *                    Calculate as VCC_measured VCC_reported. Defaults to 1.
     * @return Current VCC level, in volts.
     */
    float readVolts(const float correction = 1.0f);

    /**
     * Retrieve current VCC level. The total voltage range shall be passed
     * as lower/upper bound. For e.g. an alkaline AA battery this range can be set
     * to [0.6,..,1.5] volts.
     *
     * @param range_min  Lower bound to VCC level range, in volts.
     * @param range_max  Upper bound to VCC level range, in volts.
     * @param clip       When set, assures returned percentage is clipped to [0..100]% range.
     * @return Current VCC level, as percentage of expected VCC level.
     */
    float readPerc(const float range_min = 0, const float range_max = 0, const boolean clip = true);

    /**
     * Compute current VCC level percent from already readed value.
     * Can be usefull/more optimized if you want VCC level percent when you already have VCC level in volts
     *
     * @param volts_read 	Volts value to compute.
     * @param range_min  	Lower bound to VCC level range, in volts.
     * @param range_max  	Upper bound to VCC level range, in volts.
     * @param clip       	When set, assures returned percentage is clipped to [0..100]% range.
     * @return Computed VCC percent.
     */
    static float computePerc(const float volts_read, const float range_min = 0, const float range_max = 0, const boolean clip = true);
};

#endif 