===============
Technical notes
===============

The layer stack
===============
When activated, layers are pushed onto the top of a stack.  When deactivated,
layers are popped out from wherever they are in the stack.  Layers may be active
in the stack more than once.  When a keypress occures, the top layer is used to
determine what actions to take.

Each full layer takes 420 bytes of memory (the matrix size is 12x7, keycodes are
1 byte each, and function pointers are 2 bytes each).

Keypresses are functions
========================
Each time a key is pressed, the "press" function assigned to that key on the
current layer is called.  When the key is released, the "release" function (from
the same layer the key was on when it was pressed) is called.  These functions
may do pretty much anything - from sending multiple different keypresses to the
host, to changing the firmware state in some way, to activating a new layer.
They may also be "transparent", i.e. execute the function assigned to the key on
the layer one down from the top layer (allowing for layers that are effectively
"masks" over whatever layer was active before them).

I²C Status Codes (for Master modes)
===================================
Master Transmitter (datasheet section 20.8.1, table 20-3)
---------------------------------------------------------
* `0x08`  A START condition has been transmitted
* `0x10`  A repeated START condition has been transmitted
* `0x18`  SLA+W has been transmitted; ACK has been received
* `0x20`  SLA+W has been transmitted; NOT ACK has been received
* `0x28`  Data byte has been transmitted; ACK has been received
* `0x30`  Data byte has been transmitted; NOT ACK has been received
* `0x38`  Arbitration lost in SLA+W or data bytes

Master Receiver (datasheet section 20.8.2, table 20-4)
------------------------------------------------------
* `0x08`  A START condition has been transmitted
* `0x10`  A repeated START condition has been transmitted
* `0x38`  Arbitration lost in SLA+R or NOT ACK bit
* `0x40`  SLA+R has been transmitted; ACK has been received
* `0x48`  SLA+R has been transmitted; NOT ACK has been received
* `0x50`  Data byte has been received; ACK has been returned
* `0x58`  Data byte has been received; NOT ACK has been returned

Teensy 2.0
==========
Pinout and Pin assignments
--------------------------
* `+` indicates connected pin
* `o` indicates unconnected pin
* `=` is used to list other things the pin is connected to
* `-` inserted between some of the pin functions for readability
* `OC**` pins enclosed in parenthesis had lines over them in the pinout

Pins
----
::
                            GND +---.....---+ Vcc
                         SS PB0 +           + PF0 ADC0
                       SCLK PB1 +           + PF1 ADC1
                       MOSI PB2 +           + PF4 ADC4
                       MISO PB3 +  +     +  + PF5 ADC5
  RTS  OC1C  OC0A --------- PB7 + PE6  AREF + PF6 ADC6
             OC0B  INT0 SCL PD0 + AIN0      + PF7 ADC7
                   INT1 SDA PD1 + INT6      + PB6 ADC13 OC1B  OC4B
  RXD1 ----------- INT2 --- PD2 +           + PB5 ADC12 OC1A (OC4B)
  TXD1 ----------- INT3 --- PD3 +           + PB4 ADC11
       OC3A (OC4A) -------- PC6 +           + PD7 ADC10 T0 -- OC4D
  ICP3 ----- OC4A --------- PC7 +-+-+-+-+-+-+ PD6 ADC9  T1 - (OC4D) onboardLED
                   CTS XCK1 PD5 --/ | | | \-- PD4 ADC8 ------------ ICP1
              Vcc ------------------/ | \-------------- RST
              GND --------------------/

Pin Assignments
---------------
::
            power_negative  GND +---.....---+ Vcc  power_positive
                  column_7  PB0 +           + PF0  row_5
                  column_8  PB1 +           + PF1  row_4
                  column_9  PB2 +           + PF4  row_3
                  column_A  PB3 +  o     o  + PF5  row_2
              (OC1C) LED_3  PB7 + PE6  AREF + PF6  row_1
               (SCL)   I2C  PD0 +           + PF7  row_0
               (SDA)   I2C  PD1 +           + PB6  LED_2 (OC1B)
                  column_B  PD2 +           + PB5  LED_1 (OC1A)
                  column_C  PD3 +           + PB4  = Vcc
                  column_D  PC6 +           o PD7
                            PC7 o-o-o-o-o-o-+ PD6  onboardLED = GND
                            PD5 --/ | | | \-- PD4
                            Vcc ----/ | \---- RST
                            GND-------/

Notes
-----
* Row and column assignments are to matrix positions, which may or may or may
  not correspond to the physical position of the key: e.g. the key where `row_4`
  and `column_2` cross will be scanned into the matrix at `[4][2]`, wherever it
  happens to be located on the keyboard.  Mapping from one to the other (which
  only matters for defining layouts) is handled elsewhere.
* LEDs are labeled using numbers (starting with '1') instead of letters
  (starting with 'A') as on the PCB.
* SCL and SDA: Need external pull-up resistors.  Sometimes the Teensy internal
  pull-ups are enough (see datasheet section 20.5.1), but i think for this
  project we'll want external ones.  The general recommendation for 400kHz
  I²C seems to be 2.2kΩ.

Notes about Registers
---------------------
General I/O (see datasheet section 10.2.1)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    DDRxn  function  PORTxn  function
    1      output    1       drive high
                     0       drive low
    0      input     1       internal pull-up on
                     0       internal pull-up off

    PINxn  action   function
           write 1  toggles the value of PORTxn
           read     returns the logical value (1|0) of the pin

* Unused pins should be set as input, with internal pullup enabled in order to
  give them a defined level (see datasheet section 10.2.6).
* PD6 (the onboard LED) already has a defined level (low), so there's no reason
  to set internal pull-up enabled on it.  If we do, it will source current to
  the LED, which is fine, but unnecessary.
* Initially, we want either columns or rows (see <../options.h>) set as hi-Z
  without pull-ups, and the other set of pins set as input with pull-ups.
  During the update function, we'll cycle through setting the first set low and
  checking each pin in the second set.
  * To set a pin hi-Z on this board, set it as input with pull-up disabled.
  * Switching the driving pins (the first set of pins) between hi-Z and drive
    low (treating them as if they were open drain) seems just as good as, and a
    little safer than, driving them high when they're not active.
  * We need to delay for at least 1 μs between changing the column pins and
    reading the row pins.  I would assume this is to allow the pins time to
    stabalize.

Thanks
------
Thanks to `hasu <http://geekhack.org/member.php?3412-hasu>` for his suggestion at <http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606415&viewfull=1#post606415>, and `PrinsValium <http://geekhack.org/member.php?6408-PrinsValium>` for noting that his firmware had erratic behavior without the delays: <http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606426&viewfull=1#post606426>.  DOX tried it and confirmed that it worked for his protoype PCB (as of 3 June 2012): <http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=606865&viewfull=1#post606865>.  Before adding a delay we were having strange problems with ghosting: <http://geekhack.org/showthread.php?22780-Interest-Check-Custom-split-ergo-keyboard&p=605857&viewfull=1#post605857>.

PWM on ports OC1(A|B|C) (see datasheet section 14.10)
-----------------------------------------------------
Abbreviations
~~~~~~~~~~~~~
* OCR = Output Compare Register
* TCCR = Timer/Counter Control Register

Notes on settings
~~~~~~~~~~~~~~~~~
PWM pins should be set as outputs.

We want Waveform Generation Mode 5 (fast PWM, 8-bit) (see table 14-5); set
`TCCRB[4,3],TCCRA[1,0]` to `0,1,0,1`.

We want "Compare Output Mode, Fast PWM" to be `0b10`.
      "Clear OCnA/OCnB/OCnC on compare match, set OCnA/OCnB/OCnC at TOP"
      (see table 14-3)
      this way higher values of `OCR1(A|B|C)` will mean longer 'on' times for
      the LEDs (provided they're hooked up to GND; other way around if they're
      hooked up to Vcc)
        * when in a fast PWM mode, set `TCCR1A[7,6,5,4,3,2]` to `1,0,1,0,1,0`

We want "Clock Select Bit Description" to be `0b001`.  "clkI/O/1 (No
prescaling)" (see table 14-6).  Set `TCCR1B[2,1,0]` to `0,0,1`.  LEDs will be at
minimum brightness until OCR1(A|B|C) are changed (since the default value of all
the bits in those registers is 0).

Notes on behavior
~~~~~~~~~~~~~~~~~
The pins source current when on, and sink current when off.  They aren't set to
high impediance for either.

In Fast PWM mode setting `OCR1(A|B|C)` to `0` does not make the output on
`OC1(A|B|C)` constant low; just close.  Per the datasheet, this isn't true for
every PWM mode.

MCP23018
========
Pinout and Pin assignments
--------------------------
* `+` indicates connected pin
* `o` indicates unconnected pin
* `=` is used to list other things the pin is connected to
* `-` inserted between some of the pin functions for readability

::
  power_negative  Vss(GND) +01---.---28o NC
                        NC o02       27o GPA7
           row_5      GPB0 +03       26+ GPA6   column_6
           row_4      GPB1 +04       25+ GPA5   column_5
           row_3      GPB2 +05       24+ GPA4   column_4
           row_2      GPB3 +06       23+ GPA3   column_3
           row_1      GPB4 +07       22+ GPA2   column_2
           row_0      GPB5 +08       21+ GPA1   column_1
                      GPB6 o09       20+ GPA0   column_0
                      GPB7 o10       19o INTA
  power_positive  Vdd(Vcc) +11       18o INTB
             I2C       SCL +12       17o NC
             I2C       SDA +13       16+ RESET  = Vdd(Vcc) (see note)
                        NC o14-------15+ ADDR   = Vss(GND) (see note)

Row and column assignments are to matrix positions, which may or may or may not
correspond to the physical position of the key: e.g. the key where `row_4` and
`column_2` cross will be scanned into the matrix at `[4][2]`, wherever it
happens to be located on the keyboard.  Mapping from one to the other (which
only matters for defining layouts) is handled elsewhere.

* ADDR (pin15): Set slave address to `0b0100000` by connecting to Vss(GND).
  * The user-defined bits are the three least significant
  * I2C addresses are 7 bits long (the last bit in the byte is used for
    indicating read/write)
* RESET (pin16) must be externally biased.  Since we're not going to trigger it
  ourselves, we can tie it high.  This is not noted in the I2C Pinout
  Description section of the MCP23018 datasheet, but it's true (empirically),
  and it is noted in the SPI Pinout Description section, and in the MCP23017
  datasheet.  I'm not the first person who's failed to notice ;)
  * http://davidn.org/wp/?p=89
  * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1293498979

+----------+---------+-------------------------------------------------+
| register | address | function (for all bits)                         |
+==========+=========+=================================================+
| IODIRA   | 0x00    | 1: set corresponding pin as input               |
| IODIRB   | 0x01    | 0: set corresponding pin as output              |
+----------+---------+-------------------------------------------------+
| GPPUA    | 0x0C    | 1: set corresponding pin internal pull-up on    |
| GPPUB    | 0x0D    | 0: set corresponding pin internal pull-up off   |
+----------+---------+-------------------------------------------------+
| GPIOA    | 0x12    | read: returns the value on the port             |
| GPIOB    | 0x13    | write: modifies the OLAT register               |
+----------+---------+-------------------------------------------------+
| OLATA    | 0x14    | read: returns the value of this register        |
| OLATB    | 0x15    | write: modifies the output latches that control |
|          |         |        the pins configured as output            |
+----------+---------+-------------------------------------------------+

* IOCON register (see datasheet section 1.6, table 1-5, register 1-8)
    * BANK: bit 7; read/write; default = 0
        * 1: The registers associated with each port are separated into
          different banks
        * 0: The registers are in the same bank (addresses are sequential)
    * SEQOP: bit 5; read/write; default = 0
        * 1: Sequential operation disabled, address pointer does not increment
        * 0: Sequential operation enabled, address pointer increments

* All addresses given for IOCON.BANK = 0, since that's the default value of the
  bit, and that's what we'll be using.
* Initially, we want either columns or rows (see <../options.h>) set as hi-Z
  without pull-ups, and the other set of pins set as input with pull-ups.
  During the update function, we'll cycle through setting the first set low and
  checking each pin in the second set.

Abbreviations
~~~~~~~~~~~~~
* IODIR: I/O Direction Register
* IOCON: I/O Control Register
* GPPU:  GPIO Pull-Up Resistor Register
* GPIO:  General Purpose I/O Port Register
* OLAT:  Output Latch Register

I²C Device Protocol (see datasheet section 1.3, figure 1-1)
===========================================================
::
  S  : Start       OP   : Device opcode
  SR : Restart     ADDR : Device address
  P  : Stop        Dout : Data out from MCP23018
  W  : Write       Din  : Data in to MCP23018
  R  : Read

  S OP W ADDR ----> Din ... Din --> P
               |
               |--> SR OP R Dout ... Dout ---> P
               |<--------------------------|
               |
               |--> SR OP W ADDR ... Din --> P
               |
               |--> P

  S OP R ----> Dout ... Dout --> P
          |
          |--> SR OP R Dout ... Dout ---> P
          |<--------------------------|
          |
          |--> SR OP W ADDR Din ... Din --> P
          |
          |--> P

  Byte and Sequential Write
  -------------------------
          Byte : S OP W ADDR --> Din --> P
    Sequential : S OP W ADDR --> Din ... Din --> P

  Byte and Sequential Read
  ------------------------
          Byte : S OP W ADDR --> SR OP R Dout --> P
    Sequential : S OP W ADDR --> SR OP R Dout ... Dout --> P

We'll be using sequential mode (ICON.SEQOP = 0; default) (see datasheet section
1.3.1).

USB
===
Notes from the HID Device Class Definition, version 1.11
========================================================
* sec 4.1 (The HID Class): The `bInterfaceClass` member of an Interface
  descriptor is always 3 for HID class devices.
* sec 4.2 (Subclass): The `bInterfaceSubClass` member declares whether a device
  supports a boot interface.
  * 0 => no subclass
  * 1 => boot interface subclass
  * 2..255 => reserved

* sec 4.3 (Protocols): The `bInterfaceProtocol` member of an Interface
  descriptor only has meaning if the `bInterfaceSubClass` member declares that
  the device supports a boot interface, otherwise it is 0.
  * 0 => none
  * 1 => keyboard
  * 2 => mouse
  * 3..255 => reserved

TODO
====
Not sure where this stuff should be yet.  A lot of it (depending on what ends up
here) will likely be device and application specific.

The following document versions were used, unless otherwise noted:
* USB Specification: revision 2.0
* HID Usage Tables: version 1.12
* Device Class Definition for Human Interface Devices (HID): version 1.11

Does stuff from spec sec 9.4.* belong directly in an interrupt vector?

* spec sec 9.4.1 (Standard Device Requests / Clear Feature) (pg 252)
* spec sec 9.4.2 (Standard Device Requests / Get Configuration) (pg 253)
* spec sec 9.4.3 (Standard Device Requests / Get Descriptor) (pg 253)
* spec sec 9.4.4 (Standard Device Requests / Get Interface) (pg 254)
* spec sec 9.4.5 (Standard Device Requests / Get Status) (pg 254)
* spec sec 9.4.6 (Standard Device Requests / Set Address) (pg 256)
* spec sec 9.4.7 (Standard Device Requests / Set Configuration) (pg 257)
* spec sec 9.4.8 (Standard Device Requests / Set Descriptor) (pg 257)
* spec sec 9.4.9 (Standard Device Requests / Set Feature) (pg 258)
* spec sec 9.4.10 (Standard Device Requests / Set Interface) (pg 259)
* spec sec 9.4.11 (Standard Device Requests / Synch Frame) (pg 260)


Read the hid device class definition .pdf.  Set USB vendor  ID = 0x1d50 (Openmoko, Inc.) and USB product ID = 0x6028 (ErgoDox ergonomic keyboard).

DONE: read the hid usage tables .pdf.  I think this is more for reference and
implementation than understanding.  I've copied the relevant (i think) tables
ones into headers.  The unicode usage page, I'll have to look into more later:
I'm not sure if it can be used with keyboards.  If so though, I'll have to look
on the unicode website, or elsewhere, coz this .pdf doesn't list anything about
them out, it just references the unicode spec.
