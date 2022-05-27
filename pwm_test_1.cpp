/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "PinNames.h"
#include "PwmOut.h"

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
PwmOut led(D3);

int main()
{
    while(true) {
        // specify period first
        led.period(0.01f);      // 4 second period
        led.write(0.1f);
        ThisThread::sleep_for(1000ms);
        printf("Working...");
 //       led.write(f);
 //       ThisThread::sleep_for(1000ms);
/*
        led.period(0.005f);      // 4 second period
        led.write(0.0f);
        ThisThread::sleep_for(1000ms);
        led.write(0.10f);
        ThisThread::sleep_for(1000ms);
        led.write(0.20f);
        ThisThread::sleep_for(1000ms);
        led.write(0.30f);
        ThisThread::sleep_for(1000ms);
        led.write(0.40f);
        ThisThread::sleep_for(1000ms);
        led.write(0.50f);
        ThisThread::sleep_for(1000ms);
        led.write(0.60f);
        ThisThread::sleep_for(1000ms);
        led.write(0.70f);
        ThisThread::sleep_for(1000ms);
        led.write(0.80f);
        ThisThread::sleep_for(1000ms);
        led.write(0.90f);
        ThisThread::sleep_for(1000ms);
        led.write(1.0f);
        ThisThread::sleep_for(1000ms);
*/


        //led = 0.5f;          // shorthand for led.write()
        //led.pulsewidth(2);   // alternative to led.write, set duty cycle time in seconds
    }
}

