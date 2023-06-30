/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/student/Desktop/IoT/ArjunLab7/src/ArjunLab7.ino"
#include "env.h"
#include "blynk.h"

void setup();
void loop();
#line 4 "/Users/student/Desktop/IoT/ArjunLab7/src/ArjunLab7.ino"
#define HBUTTON D4
#define VBUTTON V5
#define VLED V0
#define TEMPSENSOR V6
#define TEMPSENSOR2 V7
#define NOTIFY_EVENT_CODE "notify"
#define HARDWARE_NOTIFY_MSG "Hardware button pressed!"
#define VIRTUAL_NOTIFY_MSG "Virtual button pressed!"

SYSTEM_THREAD(ENABLED);
#include "oled-wing-adafruit.h"
OledWingAdafruit display;
bool hardware_button_pressed = false;

void setup()
{
    pinMode(A4, INPUT);
    Serial.begin(9600);

    display.setup();
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    delay(5000);
    Blynk.begin(BLYNK_AUTH_TOKEN);
}

void loop()
{
    uint16_t reading = analogRead(A4);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    double ftemp = (temperature * 1.8) + 32;

    display.printf("%f C \n", temperature);
    display.println(" ");
    display.printf("%f F \n", ftemp);
    display.println(" ");
    display.display();

    Blynk.run();
    Blynk.virtualWrite(TEMPSENSOR, temperature);
    Blynk.virtualWrite(TEMPSENSOR2, ftemp);

    if (display.pressedA())
    {
        display.clearDisplay();
        display.println("Push Sent!");
        display.display();
        delay(5000);
        display.clearDisplay();
        Blynk.logEvent("push_notifications", "Push!");

    }


    int buttonState = digitalRead(HBUTTON);
    Blynk.virtualWrite(V0, buttonState);

    if (buttonState && !hardware_button_pressed)
    {
        Serial.println(HARDWARE_NOTIFY_MSG);

        Blynk.logEvent(NOTIFY_EVENT_CODE, HARDWARE_NOTIFY_MSG);
        hardware_button_pressed = true;
    }

    else if (!buttonState && hardware_button_pressed)
    {
        hardware_button_pressed = false;
    }
}

BLYNK_WRITE(VBUTTON)
{

    if (param.asInt())
    {
        Serial.println(VIRTUAL_NOTIFY_MSG);
        Blynk.logEvent(NOTIFY_EVENT_CODE, VIRTUAL_NOTIFY_MSG);
    }
}