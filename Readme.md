### PS 1 controller mod - additional button support for EZ-Key ###

This code is for a modified version of [this](http://imgur.com/a/mb5eN)
project. The Bluefruit EZ-Key only supports up to 12 inputs. The PS1 controller
has 14 buttons though. To have all buttons working this project utilizes the
Serial interface of the EZ-Key. Start & Select will be connected to the
ATTiny85 pins PB3 & 4. Pin change interrupts on these pins will send ASCII
chars through the serial interface to the EZ-Key. By combining the EZ-Key and
the ATTiny85 all buttons on the PS 1 controller are functional.
