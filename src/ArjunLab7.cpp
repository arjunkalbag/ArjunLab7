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
SYSTEM_THREAD(ENABLED);

#define HBUTTON D4
#define VBUTTON V5
#define TEMPSENSOR A4

#include "oled-wing-adafruit.h"
OledWingAdafruit display;

void setup()
{
    pinMode(TEMPSENSOR, INPUT);
    pinMode(D2, OUTPUT);

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

    Blynk.run();
    uint16_t reading = analogRead(A4);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    double ftemp = (temperature * 1.8) + 32;
    display.printf("%f C \n", temperature);
    display.println(" ");
    display.printf("%f F \n", ftemp);
    display.println(" ");
    display.display();
    int buttonState = digitalRead(HBUTTON);

    Blynk.virtualWrite(VBUTTON, buttonState);
    Blynk.virtualWrite(TEMPSENSOR, temperature);
}

BLYNK_WRITE(V6)
{
    uint16_t reading = analogRead(A4);
    double voltage = (reading * 3.3) / 4095.0;
    double temperature = (voltage - 0.5) * 100;
    double ftemp = (temperature * 1.8) + 32;

    if (param.asInt() == 1)
    {
        Blynk.logEvent("push_notifications", "Hey, Blynk push here!");
    }
}