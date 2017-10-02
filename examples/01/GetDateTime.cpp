
// Main.cpp
#include <Arduino.h>
#include <Ds1302.h>


Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);

const static char* WeekDays[] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

void setup()
{
    Serial.begin(9600);

    rtc.init();
    if (rtc.isHalted())
    {
        Serial.println("RTC is halted. Setting time...");

        Ds1302::DateTime dt = {
            .year = 17,
            .month = Ds1302::MONTH_OCT,
            .day = 3,
            .hour = 4,
            .minute = 51,
            .second = 30,
            .dow = Ds1302::DOW_SAT
        };

        rtc.setDateTime(&dt);
    }
}


void loop()
{
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    static uint8_t last_second = 0;
    if (last_second != now.second)
    {
        last_second = now.second;

        Serial.print("20");
        Serial.print(now.year);
        Serial.print('-');
        if (now.month < 10) Serial.print('0');
        Serial.print(now.month);
        Serial.print('-');
        if (now.day < 10) Serial.print('0');
        Serial.print(now.day);
        Serial.print(' ');
        Serial.print(WeekDays[now.dow - 1]);
        Serial.print(' ');
        if (now.hour < 10) Serial.print('0');
        Serial.print(now.hour);
        Serial.print(':');
        if (now.minute < 10) Serial.print('0');
        Serial.print(now.minute);
        Serial.print(':');
        if (now.second < 10) Serial.print('0');
        Serial.print(now.second);
        Serial.println();
    }

    delay(500);
}

