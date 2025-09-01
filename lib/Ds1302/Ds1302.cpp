/** Ds1302.cpp
 *
 * Ds1302 class.
 *
 * @version 1.0.3
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU Affero General Public License v3.0
 * @see https://github.com/Treboada/Ds1302
 *
 */

#include "Ds1302.h"

#include <Arduino.h>

#define REG_SECONDS           0x80
#define REG_MINUTES           0x82
#define REG_HOUR              0x84
#define REG_DATE              0x86
#define REG_MONTH             0x88
#define REG_DAY               0x8A
#define REG_YEAR              0x8C
#define REG_WP                0x8E
#define REG_BURST             0xBE


Ds1302::Ds1302(uint8_t pin_ena, uint8_t pin_clk, uint8_t pin_dat)
{
    _pin_ena = pin_ena;
    _pin_clk = pin_clk;
    _pin_dat = pin_dat;
    _dat_direction = INPUT;
}


void Ds1302::init()
{
    pinMode(_pin_ena, OUTPUT);
    pinMode(_pin_clk, OUTPUT);
    pinMode(_pin_dat, _dat_direction);

    digitalWrite(_pin_ena, LOW);
    digitalWrite(_pin_clk, LOW);
}


bool Ds1302::isHalted()
{
    _prepareRead(REG_SECONDS);
    uint8_t seconds = _readByte();
    _end();
    return (seconds & 0b10000000);
}


void Ds1302::getDateTime(DateTime* dt)
{
    _prepareRead(REG_BURST);
    dt->second = _bcd2dec(_readByte() & 0b01111111);
    dt->minute = _bcd2dec(_readByte() & 0b01111111);
    dt->hour   = _bcd2dec(_readByte() & 0b00111111);
    dt->day    = _bcd2dec(_readByte() & 0b00111111);
    dt->month  = _bcd2dec(_readByte() & 0b00011111);
    dt->dow    = _bcd2dec(_readByte() & 0b00000111);
    dt->year   = _bcd2dec(_readByte() & 0b11111111);
    _end();
}


void Ds1302::setDateTime(DateTime* dt)
{
    _prepareWrite(REG_WP);
    _writeByte(0b00000000);
    _end();

    _prepareWrite(REG_BURST);
    _writeByte(_dec2bcd(dt->second % 60 ));
    _writeByte(_dec2bcd(dt->minute % 60 ));
    _writeByte(_dec2bcd(dt->hour   % 24 ));
    _writeByte(_dec2bcd(dt->day    % 32 ));
    _writeByte(_dec2bcd(dt->month  % 13 ));
    _writeByte(_dec2bcd(dt->dow    % 8  ));
    _writeByte(_dec2bcd(dt->year   % 100));
    _writeByte(0b10000000);
    _end();
}


void Ds1302::halt()
{
    _setHaltFlag(true);
}


void Ds1302::start()
{
    _setHaltFlag(false);
}


void Ds1302::_setHaltFlag(bool stopped)
{
    uint8_t regs[8];
    _prepareRead(REG_BURST);
    for (int b = 0; b < 8; b++) regs[b] = _readByte();
    _end();

    if (stopped) regs[0] |= 0b10000000; else regs[0] &= ~0b10000000;
    regs[7] = 0b10000000;

    _prepareWrite(REG_WP);
    _writeByte(0b00000000);
    _end();

    _prepareWrite(REG_BURST);
    for (int b = 0; b < 8; b++) _writeByte(regs[b]);
    _end();
}


void Ds1302::_prepareRead(uint8_t address)
{
    _setDirection(OUTPUT);
    digitalWrite(_pin_ena, HIGH);
    uint8_t command = 0b10000001 | address;
    _writeByte(command);
    _setDirection(INPUT);
}


void Ds1302::_prepareWrite(uint8_t address)
{
    _setDirection(OUTPUT);
    digitalWrite(_pin_ena, HIGH);
    uint8_t command = 0b10000000 | address;
    _writeByte(command);
}


void Ds1302::_end()
{
    digitalWrite(_pin_ena, LOW);
}


uint8_t Ds1302::_readByte()
{
    uint8_t byte = 0;

    for(uint8_t b = 0; b < 8; b++)
    {
        if (digitalRead(_pin_dat) == HIGH) byte |= 0x01 << b;
        _nextBit();
    }

    return byte;
}


void Ds1302::_writeByte(uint8_t value)
{
    for(uint8_t b = 0; b < 8; b++)
    {
        digitalWrite(_pin_dat, (value & 0x01) ? HIGH : LOW);
        _nextBit();
        value >>= 1;
    }
}

void Ds1302::_nextBit()
{
        digitalWrite(_pin_clk, HIGH);
        delayMicroseconds(1);

        digitalWrite(_pin_clk, LOW);
        delayMicroseconds(1);
}


void Ds1302::_setDirection(int direction)
{
    if (_dat_direction != direction)
    {
        _dat_direction = direction;
        pinMode(_pin_dat, direction);
    }
}


uint8_t Ds1302::_dec2bcd(uint8_t dec)
{
    return ((dec / 10 * 16) + (dec % 10));
}


uint8_t Ds1302::_bcd2dec(uint8_t bcd)
{
    return ((bcd / 16 * 10) + (bcd % 16));
}


