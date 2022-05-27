/*
 * Copyright (c) 2017-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PinNames.h"
#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif


#include "mbed.h"


Ticker ticker;
DigitalOut led1(LED1);
/** The constructor takes in RX, and TX pin respectively.
  * These pins, for this example, are defined in mbed_app.json
  */
//CAN can1(MBED_CONF_APP_CAN1_RD, MBED_CONF_APP_CAN1_TD);
CAN can2(D10, D2, 500000);
char counter = 0;

/*
void send()
{
    printf("send()\n");
    if (can1.write(CANMessage(1337, &counter, 1))) {
        printf("wloop()\n");
        counter++;
        printf("Message sent: %d\n", counter);
    }
    led1 = !led1;
}
*/

int main()
{
    printf("main()\n");
//    ticker.attach(&send, 1);
    CANMessage msg;
    while (true) {
        printf("loop()\n");
        if (can2.read(msg)) {
            printf("Message received: %d\n", msg.data[0]);
            printf("Message ID: %d\n", msg.id);
            led1 = !led1;
        }
        ThisThread::sleep_for(200ms);
    }
}
