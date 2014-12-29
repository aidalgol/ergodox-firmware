/* ----------------------------------------------------------------------------
 * ergoDOX : layout matrices and layout includes
 * ----------------------------------------------------------------------------
 * Declarations for the layout const's defined in the layer module, and
 * #include's required by the layout.
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <stddef.h>
#include "lib/usb/usage-page/keyboard--short-names.h"
#include "lib/key-functions.h"
#include "matrix.h"

#ifndef KEYBOARD__ERGODOX__LAYOUT_h
#define KEYBOARD__ERGODOX__LAYOUT_h

extern const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS];
extern const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS];

#define kb_led_num_on()      _kb_led_1_on()
#define kb_led_num_off()     _kb_led_1_off()
#define kb_led_caps_on()     _kb_led_2_on()
#define kb_led_caps_off()    _kb_led_2_off()
#define kb_led_scroll_on()   _kb_led_3_on()
#define kb_led_scroll_off()  _kb_led_3_off()

#endif
