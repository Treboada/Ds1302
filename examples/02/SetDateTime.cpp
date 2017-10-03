/** SetDateTime.cpp
 *
 * Example of setting the date and time to the RTC.
 *
 * @version 1.0.1
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU Affero General Public License v3.0
 * @see https://github.com/Treboada/Ds1302
 *
 */

#include <Arduino.h>
#include <Ds1302.h>


// DS1302 RTC instance
Ds1302 rtc(PIN_ENA, PIN_CLK, PIN_DAT);


uint8_t parseDigits(char* str, uint8_t count)
{
    uint8_t val = 0;
    while(count-- > 0) val = (val * 10) + (*str++ - '0');
    return val;
}


void setup()
{
    // initialize the RTC
    rtc.init();

    Serial.begin(9600);
    Serial.println("Input the date and time (YYMMDDWhhmmss): ");
}


void loop()
{
    static char buffer[13];
    static uint8_t char_idx = 0;

    if (char_idx == 13)
    {
        // structure to manage date-time
        Ds1302::DateTime dt;

        dt.year = parseDigits(buffer, 2);
        dt.month = parseDigits(buffer + 2, 2);
        dt.day = parseDigits(buffer + 4, 2);
        dt.dow = parseDigits(buffer + 6, 1);
        dt.hour = parseDigits(buffer + 7, 2);
        dt.minute = parseDigits(buffer + 9, 2);
        dt.second = parseDigits(buffer + 11, 2);

        // set the date and time
        rtc.setDateTime(&dt);

        char_idx = 0;
    }

    if (Serial.available())
    {
        buffer[char_idx++] = Serial.read();
    }
}

