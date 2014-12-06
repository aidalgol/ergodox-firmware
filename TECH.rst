===============
Technical notes
===============

The layer stack
===============
When activated, layers are pushed onto the top of a stack.  When deactivated,
layers are popped out from wherever they are in the stack.  Layers may be active
in the stack more than once.  When a keypress occures, the top layer is used to
determine what actions to take.

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
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* `0x08`  A START condition has been transmitted
* `0x10`  A repeated START condition has been transmitted
* `0x18`  SLA+W has been transmitted; ACK has been received
* `0x20`  SLA+W has been transmitted; NOT ACK has been received
* `0x28`  Data byte has been transmitted; ACK has been received
* `0x30`  Data byte has been transmitted; NOT ACK has been received
* `0x38`  Arbitration lost in SLA+W or data bytes

Master Receiver (datasheet section 20.8.2, table 20-4)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* `0x08`  A START condition has been transmitted
* `0x10`  A repeated START condition has been transmitted
* `0x38`  Arbitration lost in SLA+R or NOT ACK bit
* `0x40`  SLA+R has been transmitted; ACK has been received
* `0x48`  SLA+R has been transmitted; NOT ACK has been received
* `0x50`  Data byte has been received; ACK has been returned
* `0x58`  Data byte has been received; NOT ACK has been returned
