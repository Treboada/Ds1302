# Ds1302

[![Travis status](https://travis-ci.org/Treboada/Ds1302.svg?branch=master)](https://travis-ci.org/Treboada/Ds1302)

A C/C++ library to use DS1302 RTC chip. 

Tested with Arduino, ESP32 and ESP8266, but easy to port to your favourite MCU.

## Examples

- [GetDateTime](https://github.com/Treboada/Ds1302/tree/master/examples/01)
- [SetDateTime](https://github.com/Treboada/Ds1302/tree/master/examples/02)

## License

This library is AGPL-3.0 licensed. See the [LICENSE][LIC01] file.


## Support

Bugs, feature requests, contributions are welcome: [Ds1302 issue tracker][ISU01].


[ISU01]: https://github.com/Treboada/Ds1302/issues
[LIC01]: LICENSE

## Changelog

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

