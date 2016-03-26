=================================
Firmware for the ErgoDox keyboard
=================================

This is a fork of `Ben Blazak's ErgoDox firmware`_.


The ErgoDox
-----------
The official website for the ErgoDox is `ErgoDox.org <http://www.ergodox.org>`_.  See also the `geekhack <http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard>`_ and `deskthority <http://deskthority.net/workshop-f7/split-ergonomic-keyboard-project-t1753.html>`_ discussion threads.  Kits are periodically for sale on Massdrop_, who also hosts `build instructions`_ and a `web UI`_ for configuring layouts.

`` _`Ben Blazak's ErgoDox firmware`: https://github.com/benblazak/ergodox-firmware
`` _Massdrop: https://www.massdrop.com/buy/ergodox
`` _`build instructions`: https://www.massdrop.com/ext/ergodox/assembly.php
`` _`web UI` https://www.massdrop.com/ext/ergodox

Flashing
--------
(These instructions are only for the CLI Teensy loader from PJRC.)

Assuming you have `teensy_loader_cli` somewhere on your `$PATH`, simply run the following commands from the `src` directory after running `make`.


teensy_loader_cli -v -mmcu=atmega32u4 -w ../ergodox-firmware/src/firmware.eep
teensy_loader_cli -v -mmcu=atmega32u4 -w ../ergodox-firmware/src/firmware.hex
