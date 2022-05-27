#include "DigitalOut.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include "mbed_events.h"
#include "PwmOut.h"
#include "mbed_power_mgmt.h"
#include <stdio.h>

#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

PwmOut led(D3);


Ticker ticker;
DigitalOut led1(LED1);
CANMessage msg;

CAN can2(D10, D2, 500000);
char counter = 0;

using namespace std::chrono_literals;

bool flashing = false;
bool buzzing = false;
bool buzzed = false;
int pin = -1;
int last_pin = -1;
bool last_flashing = false;
int id;
int lt_id = 4;
int red = 0;
int green = 1;
int blue = 2;
int buzz = 3;

PinName CAN = D2;
PinName PWM = D3;
PinName R_pin = D4;
PinName G_pin = D5;
PinName B_pin = D6;
PinName buzz_pin = D9;

DigitalOut RED(R_pin);
DigitalOut GREEN(G_pin);
DigitalOut BLUE(B_pin);
DigitalOut BUZZ(buzz_pin);
DigitalOut pins[4] = {RED, GREEN, BLUE, BUZZ};

void read_CAN () {
        //printf("Reading CAN...\n");
        if (can2.read(msg)) {
            printf("Message ID: %d\n", msg.id);
            id = msg.id;
            if (id == lt_id) {
                pin = msg.data[0];
                if (pin != buzz_pin)
                    buzzed = false;
                flashing = msg.data[1];
                printf("Pin Number: %d\n", msg.data[0]);
                printf("Flashing: %d\n", msg.data[1]);
                led1 = !led1;
            }
        }
}

void run () {
    if (last_pin != pin) {
        if(last_pin != -1) {
            pins[last_pin] = 0;
            printf("Turned off pin %d\n", last_pin);
        }
    }

    if (buzzing == true) {
        BUZZ = 0;
        buzzing = false;
        buzzed = true;
        printf("Turned off buzzer... \n");
    }
    else if (pin == buzz) {
        if (buzzed == false) {
            BUZZ = 1;
            buzzing = true;
            printf("Turned on buzzer... \n");
            pin = last_pin;
        }
    }
    else {
        if (flashing == true) {
            pins[pin] = !pins[pin];
            printf("Toggled pin %d\n", pin);
        }
        else {
            if (pin != -1) {
                pins[pin] = 1;
                printf("Turned on pin %d\n", pin);
            }
            else printf("Did nothing...");
        }
    }
    last_pin = pin;
    last_flashing = flashing;
}

void update () {
    last_pin = pin;
    last_flashing = flashing;
}

void init() {
    RED = 0;
    GREEN = 0;
    BLUE = 0;
    BUZZ = 0;
}

/*
void reset_pins () {
    RED = 0;
    GREEN = 0;
    BLUE = 0;
    BUZZ = 0;
}

void led_on (DigitalOut color) {
    color = 1;
}

void toggle (DigitalOut which_pin) {
    which_pin = !which_pin;
}

void led_off (DigitalOut color) {
    color = 0;
}
*/





// main() runs in its own thread in the OS
int main()
{   
    init();
    led.period(0.01f);      // 4 second period
    led.write(0.1f);
/*
    while(true) {
        RED = 1;
        ThisThread::sleep_for(500);
        RED = 0;
        ThisThread::sleep_for(500);
        GREEN = 1;
        ThisThread::sleep_for(500);
        GREEN = 0;
        ThisThread::sleep_for(500);
        BLUE = 1;
        ThisThread::sleep_for(500);
        BLUE = 0;
        ThisThread::sleep_for(500);
        BUZZ = 1;
        ThisThread::sleep_for(500);
        BUZZ = 0;
        ThisThread::sleep_for(500);
    }
    */
    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call_every(10ms, read_CAN);
    queue.call_every(500ms, run);

    // events are executed by the dispatch_forever method
    queue.dispatch_forever();
    
}


