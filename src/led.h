/* ----------------------------------------------------------------------------
 * ergoDOX : high-level LED-control
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#ifndef KEYBOARD__ERGODOX__LAYOUT__DEFAULT__LED_CONTROL_h
#define KEYBOARD__ERGODOX__LAYOUT__DEFAULT__LED_CONTROL_h

#include "layer.h"

// state and delay macros
#define kb_led_state_power_on() do {            \
    _kb_led_all_set_percent(LED_BRIGHTNESS/10); \
    _kb_led_all_on();                           \
  } while(0)

// note: need to delay for a total of ~1 second
#define kb_led_delay_usb_init() do {            \
    _kb_led_1_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
    _kb_led_2_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
    _kb_led_3_set_percent(LED_BRIGHTNESS);      \
    _delay_ms(333);                             \
  } while(0)

#define kb_led_state_ready() do {               \
    _kb_led_all_off();                          \
    _kb_led_all_set_percent(LED_BRIGHTNESS);    \
  } while(0)

/** Logical LED macros **
 *
 * Define unused macros to nothing, because they are all called in main.c, so
 * they need to be defined.  Any non-empty definitions should go in layout.h
 * (which must be #include'd in this file so that its definitions are in place
 * when the #ifndef's here are evaluated).
 */
#ifndef kb_led_num_on
#define kb_led_num_on()
#endif
#ifndef kb_led_num_off
#define kb_led_num_off()
#endif
#ifndef kb_led_caps_on
#define kb_led_caps_on()
#endif
#ifndef kb_led_caps_off
#define kb_led_caps_off()
#endif
#ifndef kb_led_scroll_on
#define kb_led_scroll_on()
#endif
#ifndef kb_led_scroll_off
#define kb_led_scroll_off()
#endif
#ifndef kb_led_compose_on
#define kb_led_compose_on()
#endif
#ifndef kb_led_compose_off
#define kb_led_compose_off()
#endif
#ifndef kb_led_kana_on
#define kb_led_kana_on()
#endif
#ifndef kb_led_kana_off
#define kb_led_kana_off()
#endif

#endif
