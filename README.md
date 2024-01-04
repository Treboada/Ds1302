# Ds1302

A C/C++ library to use DS1302 RTC chip. 

Tested with (but easily portable to your favourite MCU):

- [X] Arduino
- [X] ESP32 
- [X] ESP8266 

Features:

- Simple to use and manage.
- Platformio compatible.
- Control of start/stop of the oscillator.
- Secure against edge time race conditions (see [#4][ISU02]).

## Examples

- [GetDateTime][EXA01]
- [SetDateTime][EXA02]

## License

This library is AGPL-3.0 licensed. See the [LICENSE][LIC01] file.

## Support

Bugs, feature requests, contributions are welcome: [Ds1302 issue tracker][ISU01].

[EXA01]: https://github.com/Treboada/Ds1302/tree/master/examples/01
[EXA02]: https://github.com/Treboada/Ds1302/tree/master/examples/02
[ISU01]: https://github.com/Treboada/Ds1302/issues
[ISU02]: https://github.com/Treboada/Ds1302/issues/4
[LIC01]: LICENSE

## Changelog

### 1.1.0

- Start and halt oscillator without setting current timestamp (thanks
  [@photomultiplier](https://github.com/Treboada/Ds1302/pull/9))

### 1.0.5

- Bugfix: wrong mask when reading the year register (thanks
  [@photomultiplier](https://github.com/Treboada/Ds1302/pull/8))

### 1.0.4

- Library added to the Arduino Library Manager (thanks
  [@jackjansen](https://github.com/Treboada/Ds1302/issues/2))

### 1.0.3

- Bugfix: error on consecutive reads (thanks Reinhard Kopka).

### 1.0.2

- Bugfix: unable to set date 31, dow 7 and month 12.
- Platformio environment for ESP8266.

### 1.0.1

- First version.

